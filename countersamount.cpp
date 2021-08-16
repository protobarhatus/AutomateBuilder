#include "countersamount.h"

CountersAmount::CountersAmount(std::set<QString> configs_names)
{
    for (auto &it : configs_names)
    {
        this->addElement(it);
    }
}
void CountersAmount::addElement(QString name)
{
    this->amounts.insert(std::pair<QString, amount>(name, amount(new std::atomic_int(0))));
}
void CountersAmount::renameElement(QString old_name, QString new_name)
{
    auto it = this->amounts.find(old_name);
    this->amounts.insert(std::pair<QString, amount>(new_name, std::move(it->second)));
    this->amounts.erase(it);
}
void CountersAmount::eraseElement(QString name)
{
    this->amounts.erase(this->amounts.find(name));
}
void CountersAmount::setCurrent(QString name)
{
    this->current = this->amounts.find(name)->second.get();
}
std::atomic_int* CountersAmount::getCurrent()
{
    return this->current;
}
