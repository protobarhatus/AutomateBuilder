#include "arithmeticaloperator.h"

ArithmeticalOperator::ArithmeticalOperator()
{

}
void ArithmeticalOperator::setLeftOperand(std::shared_ptr<ValueElement> l)
{
    this->left = l;
}
void ArithmeticalOperator::setRightOperand(std::shared_ptr<ValueElement> r)
{
    this->left = r;
}

int OperatorPlus::getValue() const
{
    return this->left.get()->getValue() +
            this->right.get()->getValue();
}
int OperatorMinus::getValue() const
{
    return this->left.get()->getValue() -
            this->right.get()->getValue();
}
int OperatorMultiplication::getValue() const
{
    return this->left.get()->getValue() *
            this->right.get()->getValue();
}
int OperatorDivision::getValue() const
{
    return this->left.get()->getValue() /
            this->right.get()->getValue();
}
