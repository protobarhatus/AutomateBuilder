#include "logicvalueoperator.h"
#include "valueelement.h"
#include "somedataworks.h"
LogicValueOperator::LogicValueOperator()
{

}

void LogicValueOperator::setLeftOperand(std::shared_ptr<ValueElement> l)
{
    this->left = l;
}
void LogicValueOperator::setRightOperand(std::shared_ptr<ValueElement> r)
{
    this->right = r;
}

OperatorEquals::OperatorEquals()
{

}
OperatorNotEquals::OperatorNotEquals()
{

}
OperatorLess::OperatorLess()
{

}
OperatorLessEquals::OperatorLessEquals()
{

}
OperatorBigger::OperatorBigger()
{

}
OperatorBiggerEquals::OperatorBiggerEquals()
{

}
bool OperatorEquals::getValue() const
{
    return this->left->getValue() ==
            this->right->getValue();
}
bool OperatorNotEquals::getValue() const
{
    return this->left->getValue() !=
            this->right->getValue();
}
bool OperatorLess::getValue() const
{
    return this->left->getValue() <
            this->right->getValue();
}
bool OperatorLessEquals::getValue() const
{
    return this->left->getValue() <=
            this->right->getValue();
}
bool OperatorBigger::getValue() const
{
    return this->left->getValue() >
            this->right->getValue();
}
bool OperatorBiggerEquals::getValue() const
{
    return this->left->getValue() >=
            this->right->getValue();
}
bool OperatorEquals::setLeftOperandAndCompute(int left)
{
    return left == this->right->getValue();
}
bool OperatorNotEquals::setLeftOperandAndCompute(int left)
{
    return left != this->right->getValue();
}
bool OperatorLess::setLeftOperandAndCompute(int left)
{
    return left < this->right->getValue();
}
bool OperatorLessEquals::setLeftOperandAndCompute(int left)
{
    return left <= this->right->getValue();
}
bool OperatorBigger::setLeftOperandAndCompute(int left)
{
    return left > this->right->getValue();
}
bool OperatorBiggerEquals::setLeftOperandAndCompute(int left)
{
    return left >= this->right->getValue();
}
QString OperatorEquals::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " == " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorNotEquals::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " != " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorLess::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " < " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorLessEquals::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " <= " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorBigger::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " > " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorBiggerEquals::reBuildStringFormula() const
{
    return getExpressionAsArgument(this->left->reBuildStringFormula()) + " >= " +
            getExpressionAsArgument(this->right->reBuildStringFormula());
}
QString OperatorEquals::getStringRepresentation()
{
    return "==";
}
QString OperatorNotEquals::getStringRepresentation()
{
    return "!=";
}
QString OperatorLess::getStringRepresentation()
{
    return "<";
}
QString OperatorLessEquals::getStringRepresentation()
{
    return "<=";
}
QString OperatorBigger::getStringRepresentation()
{
    return ">";
}
QString OperatorBiggerEquals::getStringRepresentation()
{
    return ">=";
}
