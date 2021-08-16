#include "logicvalue.h"

LogicValue::LogicValue(bool val)
{
    this->value = val;
}

bool LogicValue::getValue() const
{
    return this->value;
}
QString LogicValue::reBuildStringFormula() const
{
    return this->value ? "true" : "false";
}
