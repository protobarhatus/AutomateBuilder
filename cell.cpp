#include "cell.h"

Cell::Cell()
{

}
Cell::~Cell()
{

}
Statement * Cell::getStatement()
{
    return this->statement;
}
void Cell::setStatement(Statement * st)
{

    this->statement = st;

}

Cell & Cell::operator=(const Cell & cell)
{
    //Да, копируется именно указатель, а не его значение
    this->statement = cell.statement;
    return *this;
}
