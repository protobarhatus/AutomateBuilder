#include "statementscounter.h"
#include "statement.h"
SingleCounter::SingleCounter()
{

}
template<class T, class U>
void copyTo(std::unordered_map<T, U> * left, const std::map<T, U> & right)
{
    left->clear();
    for (auto &it : right)
    {
        left->insert(std::pair<T, U>(it.first, it.second));
    }
}

SingleCounter & SingleCounter::getCounter()
{
    static SingleCounter counter;
    return counter;
}
void SingleCounter::setStatementsList(const std::map<int, Statement*> & istatements)
{
    copyTo(&this->statements, istatements);
    this->amounts.clear();
    for (auto &it : istatements)
    {
        this->amounts.insert(std::pair<int, CountersAmount>(it.first, CountersAmount(this->configurations_list)));
    }
}
void SingleCounter::increaseCounter(int number_of_element)
{
    auto it = this->amounts.find(number_of_element);
    if (it == this->amounts.end())
        return;
    ++(*(it->second.getCurrent()));
}
void SingleCounter::decreaseCounter(int number_of_element)
{
    auto it = this->amounts.find(number_of_element);
    if (it == this->amounts.end())
        return;
    --(*(it->second.getCurrent()));
}
int SingleCounter::getAmountOfElements(int number_of_element)
{
   auto it = this->amounts.find(number_of_element);
   if (it == this->amounts.end())
       return 0;
   return *it->second.getCurrent();
}
void SingleCounter::setElementsListWithSavingAllPositions(const std::map<int, Statement*> & istatements)
{
    copyTo(&this->statements, istatements);
    for (auto &it : istatements)
    {
        if (this->amounts.find(it.first) == this->amounts.end())
        {

            this->amounts.insert(std::pair<int, CountersAmount>(it.first, CountersAmount(this->configurations_list)));
        }
    }
}
void SingleCounter::updateStatementsNumber()
{
    std::unordered_map<int, CountersAmount> copy;
    for (auto &it : this->amounts)
    {

        copy.insert(std::pair<int, CountersAmount>(this->statements.find(it.first)->second->getNumber(),
                                                         std::move(it.second)));
    }
    this->amounts = std::move(copy);
    std::unordered_map<int, Statement*> new_statements;
    for (auto &it : this->statements)
    {
        new_statements.insert(std::pair<int, Statement*>(it.second->getNumber(), it.second));
    }
    this->statements = std::move(new_statements);
}
void SingleCounter::addElement(int number, Statement * statement)
{
    if (this->amounts.find(number) != this->amounts.end())
        return;

    this->amounts.insert(std::pair<int, CountersAmount>(number, CountersAmount(this->configurations_list)));
    this->statements.insert(std::pair<int, Statement*>(number, statement));
}
void SingleCounter::deleteElement(int number)
{
    auto it = this->amounts.find(number);
    if (it == this->amounts.end())
        return;
    this->amounts.erase(it);
    this->statements.erase(this->statements.find(number));
}
void SingleCounter::addConfiguration(QString name)
{
    this->configurations_list.insert(name);
    for (auto &it : this->amounts)
    {
        it.second.addElement(name);
    }
}
void SingleCounter::renameConfiguration(QString old_name, QString new_name)
{
    this->configurations_list.erase(this->configurations_list.find(old_name));
    this->configurations_list.insert(new_name);
    for (auto &it: this->amounts)
    {
        it.second.renameElement(old_name, new_name);
    }


}
void SingleCounter::eraseConfiguration(QString name)
{
    this->configurations_list.erase(this->configurations_list.find(name));
    for (auto &it: this->amounts)
    {
        it.second.eraseElement(name);
    }
}
void SingleCounter::selectConfiguration(QString name)
{
    for (auto &it : this->amounts)
    {
        it.second.setCurrent(name);
    }
}
