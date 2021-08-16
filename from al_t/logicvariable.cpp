#include "logicvariable.h"

LogicVariable::LogicVariable(QString iname, bool ivalue)
{
    this->name = iname;
    this->value = ivalue;
}
LogicVariable::LogicVariable(QString iname)
{
    this->name = iname;
}
bool LogicVariable::getValue() const
{
    return this->value;
}

bool operator<(LogicVariable left, LogicVariable right)
{
    return left.name < right.name;
}
