#include "algorithm.h"

Algorithm::Algorithm()
{

}

void Algorithm::addLogicVariable(QString name, bool value)
{
    LogicVariable variable(name, value);
    bool is_name_free =
        this->logic_variable_list.find(name) == this->logic_variable_list.end();
    if (!is_name_free)
    {
        throw (QString)"Variable with this name is already exists";
    }
    this->logic_variable_list.insert(std::pair<QString,
                                     LogicVariable>(name, variable));
}
void Algorithm::addStatement(QString name, int number, TQPixmap sprite)
{
    bool is_name_free =
            this->statements_list.find(name) ==
            this->statements_list.end();
    if (!is_name_free)
    {
        throw (QString)"Statement with this name is \
        already exists";
    }
    bool is_number_free = this->statements_number_list.find(number) ==
            this->statements_number_list.end();
    if (!is_number_free)
    {
        throw (QString)"Statement with this number is already \
        exists";
    }
    Statement statement(name, number, sprite);
    auto it = this->statements_list.insert(
                std::pair<QString, Statement>(name, statement));
    this->statements_number_list.insert(
                std::pair<int, Statement*>(number, &it.first->second));
}
