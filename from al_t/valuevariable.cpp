#include "valuevariable.h"

ValueVariable::ValueVariable(QString iname, int ivalue)
{
    this->name = iname;
    this->value = ivalue;
}
ValueVariable::~ValueVariable()
{

}

ValueVariable::ValueVariable(QString iname)
{
    this->name = iname;
}

int ValueVariable::getValue() const
{
    return this->value;
}


