#include "value.h"

Value::Value(int val)
{
    this->value = val;
}

int Value::getValue() const
{
    return this->value;
}
