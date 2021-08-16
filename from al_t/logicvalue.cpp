#include "logicvalue.h"

LogicValue::LogicValue(bool val)
{
    this->value = val;
}

bool LogicValue::getValue() const
{
    return this->value;
}
