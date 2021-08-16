#include "statement.h"

Statement::Statement(QString iname, int inumber, TQPixmap isprite)
{
    this->name = iname;
    this->number = inumber;
   // this->sprite = isprite;
}
void Statement::setSprite(TQPixmap isprite)
{
    this->sprite = isprite;
}
void Statement::setNumber(int inumber)
{

    this->number = inumber;
}
void Statement::setName(QString iname)
{
    this->name = iname;
}
TQPixmap Statement::getSprite()
{
    return this->sprite;
}
int Statement::getNumber()
{
    return this->number;
}
QString Statement::getName()
{
    return this->name;
}
