#ifndef FIELD_H
#define FIELD_H
#include "cell.h"
#include <memory>
#include <QString>
#include <functioncell.h>
#include <vector>
#include <queue>
#include <QDebug>
#include "statementscounter.h"
#include <thread>
#include <map>
#include <unordered_map>
#include <shared_mutex>
#include <atomic>
#include "thread.h"
class Algorithm;

class Field
{
public:
    Field();
    ~Field();
    void setAlgorithm(Algorithm *);
    void InitializeField(int width, int height, Statement * default_statement);
    //выполняет необходимые действия перед запуском симуляции (не относится к снятию с паузы)
    void launch();
    //представляет кнопку "стоп" - сбрасывает все до начального состояния (initial_field)
    void reset();
    //заполняет все поле default_statement
    void clear();
    //меняет first и second, что представляет собой двойную буферизацию без копирования
    void swap();
    //проходит по всем клеткам, вызывая для каждой Algorithm::doLocalPartOfIteration(), при этом сохраняя координаты обрабаты-
    //ваемой клетки
    void iterate();
    //если координаты выходят за границы поля, возвращается nullptr
    Statement * getStatementOfCellRelativelyToTheCurrent(int x, int y);
    //проверяет, не выйдет ли за границы поля, если к current_x или current_y прибавить x и y
    bool isInField(int x, int y);
    Statement * getStatementOfCell(int x, int y);
    //данная функция, по идее, вызывается редактором, поэтому записывает состояние в first
    void setStatement(int x, int y, Statement * statement);
    //данная функция, по идее, вызывается action-ами, поэтому записывает состояние в second
    void setStatementToTheCurrent(Statement * statement, bool write_to_counter = true);
//вектор с функциями окружения должен содержать только те функции, которые определяют окрестность (allowed)
    void doWaveRelativelyToTheCurrent(const std::vector<std::shared_ptr<FunctionCell>> & environs_functions, int radius, std::function<void (int, int)> wrightCell);
    void doWaveRelativelyToTheCentre(const std::vector<std::shared_ptr<FunctionCell>> & environs_functions, int radius, std::function<void (int, int)> wrightCell);
    template<class T>
    void doWaveRelativelyToTheCurrent(const std::vector<std::shared_ptr<FunctionCell>> & environs_functions, int radius, std::function<void (Statement * st, T * params) > doSomething, T * params)
    {
        this->doWaveRelativelyToTheCurrent(environs_functions, radius, [this, &doSomething, params](int x, int y) {
            doSomething(this->getStatementOfCellRelativelyToTheCurrent(x, y), params);
        });
    }
    void initializeThreads();
private:
    void deleteField();
    //два массива представляют собой два поля. двойная буферизация необходима для сохранения одного из главных
    //свойств клеточного автомата - результат итерации не завсит от порядка выполнения ячеек. Использовать их следует только
    //через указатели first и second, т. к. тогда не нужно после завершения итерации копировать второй массив в первый.

    Cell ** bl_first_field;

    Cell ** bl_second_field;

    Cell *** first;

    Cell *** second;

    bool has_initialized = false;
    int width, height;
    std::vector<Thread> threads;
    Statement * default_statement;

    Cell ** initial_field;
    //координаты клетки, которая просчитывается в итерации. применяются для функций, вызываемых формулами. позиция в векторе
    //совпадает с номером, гарантируется field::iterate()
    std::vector<QPoint> current_cell;
    //std::unordered_map<std::thread::id, std::unique_ptr<QPoint>> current_cell;
    //std::shared_mutex mut;
    //не учитывая главный
    std::atomic_int amount_of_open_threads;
    Algorithm * algorithm;
    Field & operator=(const Field &) = delete;
    Field(const Field &) = delete;
    SingleCounter & counter;
};

#endif // FIELD_H
