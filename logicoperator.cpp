#include "logicoperator.h"
#include "somedataworks.h"
LogicOperator::LogicOperator()
{

}

void LogicOperator::setLeftOperand(std::shared_ptr<LogicElement> l)
{
    this->left = l;
}
void LogicOperator::setRightOperand(std::shared_ptr<LogicElement> r)
{
    this->right = r;
}
OperatorAND::OperatorAND()
{

}
OperatorNAND::OperatorNAND()
{

}
OperatorNOR::OperatorNOR()
{

}
OperatorOR::OperatorOR()
{

}
OperatorXNOR::OperatorXNOR()
{

}
OperatorXOR::OperatorXOR()
{

}
bool OperatorAND::getValue() const
{
    return this->left->getValue() &&
            this->right->getValue();
}
bool OperatorOR::getValue() const
{
    return this->left->getValue() ||
            this->right->getValue();
}
bool OperatorNAND::getValue() const
{
    return !this->left->getValue() &&
             !this->right->getValue();
}
bool OperatorNOR::getValue() const
{
    return !(this->left->getValue() ||
             this->right->getValue());
}
bool OperatorXOR::getValue() const
{
    return this->left->getValue() !=
            this->right->getValue();
}
bool OperatorXNOR::getValue() const
{
    return this->left->getValue() ==
            this->right->getValue();
}
QString OperatorAND::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " AND " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorOR::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " OR " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorNAND::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " NAND " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorNOR::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " NOR " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorXOR::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " XOR " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorXNOR::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " XNOR " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
