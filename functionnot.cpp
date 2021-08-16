#include "functionnot.h"
#include "somedataworks.h"
FunctionNot::FunctionNot()
{

}
void FunctionNot::setExpression(std::shared_ptr<LogicElement> expr)
{
    this->expression = expr;
}
bool FunctionNot::getValue() const
{
    return !this->expression->getValue();
}
QString FunctionNot::reBuildStringFormula() const
{
    return "[NOT " + getExpressionAsArgument(this->expression->reBuildStringFormula()) + "]";
}
