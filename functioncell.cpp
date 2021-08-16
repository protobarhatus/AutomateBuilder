#include "functioncell.h"
#include <QRegularExpression>
#include "field.h"
#include "fielddistributor.h"
FunctionCell::FunctionCell(QString iname, int x, int y, bool iis_allowed, FieldDistributor * ifield)
{
    this->X = x;
    this->Y = y;
    this->name = iname;
    this->is_allowed = iis_allowed;
    this->field = ifield;
}
int FunctionCell::getValue() const
{
    Statement * statement = (*this->field)->getStatementOfCellRelativelyToTheCurrent(this->X, this->Y);
    if (!statement)
        return std::numeric_limits<int>::quiet_NaN();
    return (*this->field)->getStatementOfCellRelativelyToTheCurrent(this->X, this->Y)->getNumber();
}
QString FunctionCell::reBuildStringFormula() const
{
    return this->name;
}
void FunctionCell::setPermissibility(bool iis_allowed)
{
    this->is_allowed = iis_allowed;
}
bool FunctionCell::isAllowed()
{
    return this->is_allowed;
}
QString FunctionCell::getDefinition()
{
    QString str_x, str_y;
    str_x.setNum(this->X);
    str_y.setNum(this->Y);
    return "{" + str_x + ", " + str_y + "}";
}
QString FunctionCell::getName()
{
    return this->name;
}
int FunctionCell::getX() const
{
    return this->X;
}
int FunctionCell::getY() const
{
    return this->Y;
}
void FunctionCell::setName(QString iname)
{
    this->name = iname;
}
void FunctionCell::setX(int x)
{
    this->X = x;
}
void FunctionCell::setY(int y)
{
    this->Y = y;
}
