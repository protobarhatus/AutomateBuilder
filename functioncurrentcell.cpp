#include "functioncurrentcell.h"
#include <QDebug>
#include "field.h"
#include "fielddistributor.h"
FunctionCurrentCell::FunctionCurrentCell(FieldDistributor * ifield)
{
    this->field = ifield;
}

int FunctionCurrentCell::getValue() const
{
    return (*this->field)->getStatementOfCellRelativelyToTheCurrent(0, 0)->getNumber();
}
QString FunctionCurrentCell::reBuildStringFormula() const
{
    return "CURRENT_CELL";
}
