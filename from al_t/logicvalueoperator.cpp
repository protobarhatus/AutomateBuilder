#include "logicvalueoperator.h"
#include "valueelement.h"
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

bool OperatorEquals::getValue() const
{
    return this->left.get()->getValue() ==
            this->right.get()->getValue();
}
bool OperatorNotEquals::getValue() const
{
    return this->left.get()->getValue() !=
            this->right.get()->getValue();
}
bool OperatorLess::getValue() const
{
    return this->left.get()->getValue() <
            this->right.get()->getValue();
}
bool OperatorLessEquals::getValue() const
{
    return this->left.get()->getValue() <=
            this->right.get()->getValue();
}
bool OperatorBigger::getValue() const
{
    return this->left.get()->getValue() >
            this->right.get()->getValue();
}
bool OperatorBiggerEquals::getValue() const
{
    return this->left.get()->getValue() >=
            this->right.get()->getValue();
}
