#include "arithmeticaloperator.h"
#include "somedataworks.h"
#include <math.h>
ArithmeticalOperator::ArithmeticalOperator()
{

}
void ArithmeticalOperator::setLeftOperand(std::shared_ptr<ValueElement> l)
{
    this->left = l;
}
void ArithmeticalOperator::setRightOperand(std::shared_ptr<ValueElement> r)
{
    this->right = r;
}
OperatorPlus::OperatorPlus()
{

}
OperatorMinus::OperatorMinus()
{

}
OperatorMultiplication::OperatorMultiplication()
{

}
OperatorDivision::OperatorDivision()
{

}
OperatorRemainder::OperatorRemainder()
{

}
OperatorDivisionWithRounding::OperatorDivisionWithRounding()
{

}
int OperatorPlus::getValue() const
{
    return this->left->getValue() +
            this->right->getValue();
}
int OperatorMinus::getValue() const
{
    return this->left->getValue() -
            this->right->getValue();
}
int OperatorMultiplication::getValue() const
{
    return this->left->getValue() *
            this->right->getValue();
}
int OperatorDivision::getValue() const
{
    return this->left.get()->getValue() /
            this->right->getValue();
}
int OperatorRemainder::getValue() const
{
    return this->left->getValue() %
            this->right->getValue();
}
int OperatorDivisionWithRounding::getValue() const
{
    return int(roundf(float(this->left->getValue()) / this->right->getValue()));
}
QString OperatorPlus::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " + " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorMinus::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " - " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorMultiplication::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " * " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorDivision::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " / " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorDivisionWithRounding::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " // " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorRemainder::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " % " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
