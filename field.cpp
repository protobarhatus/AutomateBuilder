#include "field.h"
#include "algorithm.h"
#include <queue>
#include "somedataworks.h"
#include <thread.h>
#include <atomic>
Field::Field() : counter(SingleCounter::getCounter())
{

}

void Field::initializeThreads()
{

    int amount_of_threads = std::thread::hardware_concurrency();
    this->threads = std::vector<Thread>(amount_of_threads);
    for (int i = 0; i < amount_of_threads; ++i)
    {
        this->threads[i].setId(i);
    }
    this->algorithm->amountOfThreadsChanged(amount_of_threads);
}
Field::~Field()
{
    this->deleteField();

}
void Field::InitializeField(int iwidth, int iheight, Statement * idefault_statement)
{
    this->deleteField();
    this->initializeThreads();
    this->width = iwidth;
    this->height = iheight;
    this->default_statement = idefault_statement;

    this->bl_first_field = new Cell*[iwidth];
    this->bl_second_field = new Cell*[iwidth];
    this->initial_field = new Cell*[iwidth];
    for (int i = 0; i < iwidth; ++i)
    {
        this->bl_first_field[i] = new Cell[iheight];
        this->bl_second_field[i] = new Cell[iheight];
        this->initial_field[i] = new Cell[iheight];
        for (int k = 0; k < iheight; ++k)
        {
            this->bl_first_field[i][k].setStatement(idefault_statement);
            this->counter.increaseCounter(this->default_statement->getNumber());
        }
    }

    this->first = &this->bl_first_field;
    this->second = &this->bl_second_field;
    this->has_initialized = true;

}
void Field::setAlgorithm(Algorithm * alg)
{
    this->algorithm = alg;
}
void Field::launch()
{

    for (int x = 0; x < this->width; ++x)
    {
        for (int y = 0; y < this->height; ++y)
        {

            (*this->second)[x][y] = (*this->first)[x][y];
            this->initial_field[x][y] = (*this->first)[x][y];
        }
    }


}
void Field::reset()
{
    for (int x = 0; x < this->width; ++x)
    {
        for (int y = 0; y < this->height; ++y)
        {
            this->setStatement(x, y, this->initial_field[x][y].getStatement());
        }
    }
}
void Field::clear()
{
    for (int x = 0; x < this->width; ++x)
    {
        for (int y = 0; y < this->height; ++y)
        {
            this->setStatement(x, y, this->default_statement);
        }
    }
}
void Field::swap()
{
    Cell *** temp;
    temp = first;
    first = second;
    second = temp;
}

void Field::iterate()
{

    int standart_width = divideWithRoundingToBigger(this->width, this->threads.size()),
            standart_height = this->height;
    auto iterate_small_part = [standart_width, standart_height, this](int x, int y, int thread_id)->void {
        int xend = (x + standart_width < this->width ? x + standart_width : this->width);
        int yend = (y + standart_height < this->height ? y + standart_height : this->height);
        for (; x < xend; ++x)
        {
            this->current_cell[thread_id].setX(x);
            for (int cy = y; cy < yend; ++cy)
            {
                 this->current_cell[thread_id].setY(cy);
                //qDebug() << "coping current statement: " << this->getStatementOfCellRelativelyToTheCurrent(0, 0);
                this->setStatementToTheCurrent(this->getStatementOfCellRelativelyToTheCurrent(0, 0), false);
              //  qDebug() << "starting to complite rules";
                algorithm->doLocalPartOfIteration();
            }
        }
        this->amount_of_open_threads--;
    };
    //qDebug() << "starting the iteration";
    this->current_cell.clear();
    for (auto &it : this->threads)
    {
        int threads_id = it.getId();
        this->current_cell.push_back(QPoint(threads_id * standart_width, 0));

        it.setMainFunction([threads_id, standart_width, &iterate_small_part]() {
            iterate_small_part(threads_id * standart_width, 0, threads_id);
        });
     }
    this->amount_of_open_threads.store(this->threads.size());
    for (auto &it : this->threads)
        it.start();
    while(this->amount_of_open_threads != 0) {}
    this->swap();
   // qDebug() << "iteration finished";
}
bool Field::isInField(int x, int y)
{
    return !(x < 0) && !(y < 0) &&
            !(x >= this->width) && !(y >= this->height);
}
Statement * Field::getStatementOfCellRelativelyToTheCurrent(int x, int y)
{
    //this->mut.lock_shared();
    //QPoint *current = this->current_cell.find(std::this_thread::get_id())->second.get();
    //this->mut.unlock_shared();
    QPoint current = this->current_cell[Thread::currentId()];
    if (!this->isInField(current.x() + x, current.y() + y))
        return nullptr;
    return (*this->first)[current.x() + x][current.y() + y].getStatement();
}
void Field::setStatementToTheCurrent(Statement * statement, bool write_to_counter)
{
   // this->mut.lock_shared();
    //QPoint *current = this->current_cell.find(std::this_thread::get_id())->second.get();
    //this->mut.unlock_shared();
    QPoint current = this->current_cell[Thread::currentId()];
    //т. к. класс гарантирует валидность current_ координат, проверка не требуется
   // qDebug() << "setting statement: " << statement << "with number: " << statement->getNumber();
    //qDebug() << "bl_first: " << this->bl_first_field << " with statement " << this->bl_first_field[0][0].getStatement();
   // qDebug() << "bl_second: " << this->bl_second_field << "with statement " << this->bl_second_field[0][0].getStatement();
   // qDebug() << "first: " << *this->first << "with statement " << (*this->first)[0][0].getStatement();
    //qDebug() << "second: " << *this->second << "with statement " << (*this->second)[0][0].getStatement();
    (*this->second)[current.x()][current.y()].setStatement(statement);
    //qDebug() << "statement setted. the new statement at second is: " << (*this->second)[0][0].getStatement();
    if (write_to_counter)
    {
        counter.decreaseCounter((*this->first)[current.x()][current.y()].getStatement()->getNumber());
        counter.increaseCounter(statement->getNumber());
    }
}
Statement * Field::getStatementOfCell(int x, int y)
{
    if (!this->isInField(x, y))
        return nullptr;
    return (*this->first)[x][y].getStatement();
}
/*
template<class T>
 void Field::doWaveRelativelyToTheCurrent(const std::vector<std::shared_ptr<FunctionCell>> & environs_functions, int radius, std::function<void (Statement * st, T * params) > doSomething, T * params)
 {
     bool ** has_checked = new bool*[this->width];
     for (int i = 0; i < this->width; ++i)
         has_checked[i] = new bool[this->height];
     std::deque<std::pair<int, int>> current_cells;
     current_cells.push_back(std::pair<int, int>(this->current_x, this->current_y));
     std::deque<std::pair<int, int>> future_cells;
     std::deque<std::pair<int, int>> * current_cells_pointer = &current_cells;
     std::deque<std::pair<int, int>> * future_cells_pointer = &future_cells;
     for (int i = 0; i < radius; ++i)
     {
         future_cells_pointer->clear();
         for (auto &cell : *current_cells_pointer)
         {
             for (auto &function : environs_functions)
             {
                 int new_x = function->getX() + cell.first, new_y = function->getY() + cell.second;
                 if (!has_checked[new_x][new_y])
                 {
                     has_checked[new_x][new_y] = true;
                     future_cells_pointer->push_back(std::pair<int, int>(new_x, new_y));
                     doSomething(this->getStatementOfCell(new_x, new_y), params);
                 }
             }
         }
         auto temp = current_cells_pointer;
         current_cells_pointer = future_cells_pointer;
         future_cells_pointer = temp;
     }
     for (int i = 0; i < this->width; ++i)
         delete [] has_checked[i];
     delete [] has_checked;
 }
*/
void Field::setStatement(int x, int y, Statement * statement)
{
    if (!this->isInField(x, y))
        return;
    if (statement == nullptr)
        return;
    counter.decreaseCounter((*this->first)[x][y].getStatement()->getNumber());
    counter.increaseCounter(statement->getNumber());
    (*this->first)[x][y].setStatement(statement);
}

void Field::deleteField()
{
    if (this->has_initialized)
    {
        qDebug() << "STDEL: " << SingleCounter::getCounter().getAmountOfElements(0);
        for (int i = 0; i < this->width; ++i)
        {
            for (int k = 0; k < this->height; ++k)
            {
                this->counter.decreaseCounter((*this->first)[i][k].getStatement()->getNumber());
            }
            delete [] this->bl_first_field[i];

            delete [] this->bl_second_field[i];
            delete [] this->initial_field[i];
        }
        delete [] this->bl_first_field;
        delete [] this->bl_second_field;
        delete [] this->initial_field;
        qDebug() << "ENDDEL: " << SingleCounter::getCounter().getAmountOfElements(0);
    }
}
void Field::doWaveRelativelyToTheCurrent(const std::vector<std::shared_ptr<FunctionCell>> & environs_functions, int radius,
                                         std::function<void (int, int)> wrightCell)
{
    bool ** has_checked = new bool*[this->width];
    for (int i = 0; i < this->width; ++i)
    {
        has_checked[i] = new bool[this->height];
        for (int k = 0; k < this->height; ++k)
            has_checked[i][k] = false;
    }
    QPoint current = this->current_cell[Thread::currentId()];
    has_checked[current.x()][current.y()] = true;
    std::deque<std::pair<int, int>> current_cells;
    current_cells.push_back(std::pair<int, int>(current.x(), current.y()));
    std::deque<std::pair<int, int>> future_cells;
    std::deque<std::pair<int, int>> * current_cells_pointer = &current_cells;
    std::deque<std::pair<int, int>> * future_cells_pointer = &future_cells;
    for (int i = 0; i < radius; ++i)
    {
        future_cells_pointer->clear();
        for (auto &cell : *current_cells_pointer)
        {
            for (auto &function : environs_functions)
            {
                int new_x = function->getX() + cell.first, new_y = function->getY() + cell.second;
                if (isInField(new_x, new_y))
                {
                    if (!has_checked[new_x][new_y])
                    {
                        has_checked[new_x][new_y] = true;
                        future_cells_pointer->push_back(std::pair<int, int>(new_x, new_y));
                        wrightCell(new_x - current.x(), new_y - current.y());
                    }
                }

            }
        }
        auto temp = current_cells_pointer;
        current_cells_pointer = future_cells_pointer;
        future_cells_pointer = temp;
    }
    for (int i = 0; i < this->width; ++i)
        delete [] has_checked[i];
    delete [] has_checked;
}
//она должна вызываться только в global-time, соответственно, current_cell должен быть пустой
void Field::doWaveRelativelyToTheCentre(const std::vector<std::shared_ptr<FunctionCell>> & environs_functions, int radius,
                                        std::function<void (int, int)> wrightCell)
{
    //this->current_cell.insert(std::pair<std::thread::id, std::unique_ptr<QPoint>>(
     //                             std::this_thread::get_id(), std::move(std::unique_ptr<QPoint>(new QPoint(this->width / 2, this->height / 2)))));
    //эмуляция достаточно большой карты для того, чтобы функция получила все необходимые функции окружения
    int old_width = this->width, old_height = this->height;
    this->width = radius * 2 + 1;
    this->height = radius * 2 + 1;
    this->current_cell.push_back(QPoint(this->width / 2, this->height / 2));
    Thread thread;
    std::atomic_bool has_done;
    has_done.store(false);
    thread.setMainFunction([this, &environs_functions, radius, &wrightCell, &has_done]() mutable {
        this->doWaveRelativelyToTheCurrent(environs_functions, radius, wrightCell);
        has_done.store(true);
    });
    thread.setId(0);
    thread.start();
    while (!has_done) {}
    this->width = old_width;
    this->height = old_height;
    this->current_cell.clear();
}
