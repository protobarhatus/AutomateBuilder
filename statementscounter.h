#ifndef STATEMENTSCOUNTER_H
#define STATEMENTSCOUNTER_H
#include <map>
#include <unordered_map>
#include <memory>
#include <atomic>
#include "countersamount.h"
class Statement;


//синглтон, который занимается подсчетом количества различных состояний в field. Впринципе, его несложно переделать под
//универсальный класс. Здесь я использую map с указателями statement, т. к. лень писать перевод в set. Однако убрать упоминания
//Statement, и, возможно, ввести шаблон на идентификатор (здесь использую int), и универсальный класс готов. Правда, он синглтон, и
//в один момент может заниматься подсчетом только одной группы объектов.

//однако, чтобы корректно отсчитывать состояния различных конфигураций, теперь он хранит несколько значений для одного ключа
//и дополнительный ключ для этих значений, а также список этих ключей
class SingleCounter
{
public:
    static SingleCounter & getCounter();
    void setStatementsList(const std::map<int, Statement*> & statements);
    //добавляет только те элементы из списка, которых еще нет в таблице класса. Вызывается, если состояния только добавлялись
    void setElementsListWithSavingAllPositions(const std::map<int, Statement*> & statements);
    //метод чисто для этой программы, обновляющий номера состояний если они изменились
    void updateStatementsNumber();
    //ничего не делает, если элемента с данным номером нет в этом классе
    void increaseCounter(int number_of_element);
    void decreaseCounter(int number_of_element);
    //вернет 0, если в этом классе нет элемента с данным номером
    int getAmountOfElements(int number_of_element);
    //ничего не делает, если элемент с данным номером уже существует
    void addElement(int number, Statement * statement);
    //ничего не делает, есди элемента с данным номером не существует
    void deleteElement(int number);

    void addConfiguration(QString name);
    void renameConfiguration(QString old_name, QString new_name);
    void eraseConfiguration(QString name);
    void selectConfiguration(QString name);
private:
    SingleCounter();
    SingleCounter(const SingleCounter &) = delete;
    SingleCounter & operator=(const SingleCounter &) = delete;
    //данная таблица нужна конкретно в этой программе
    std::unordered_map<int, Statement*> statements;
    //здесь использовались указатели, потому что второй элемент представляет кол-во объектов, и его надо изменять, а map это
    //запрещает. теперь тут обертка над ними
    std::unordered_map<int, CountersAmount> amounts;
    std::set<QString> configurations_list;

};

#endif // STATEMENTSCOUNTER_H
