#include "value.h"

Value::Value(int val)
{
    this->value = val;
}

int Value::getValue() const
{
    return this->value;
}
QString Value::reBuildStringFormula() const
{
    QString value_in_string;
    value_in_string.setNum(this->value);
    return value_in_string;
}
