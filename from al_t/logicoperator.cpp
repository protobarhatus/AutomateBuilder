#include "logicoperator.h"

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

bool OperatorAND::getValue() const
{
    return this->left.get()->getValue() &&
            this->right.get()->getValue();
}
bool OperatorOR::getValue() const
{
    return this->left.get()->getValue() ||
            this->right.get()->getValue();
}
bool OperatorNAND::getValue() const
{
    return !this->left.get()->getValue() &&
             !this->right.get()->getValue();
}
bool OperatorNOR::getValue() const
{
    return !(this->left.get()->getValue() ||
             this->right.get()->getValue());
}
bool OperatorXOR::getValue() const
{
    return this->left.get()->getValue() !=
            this->right.get()->getValue();
}
bool OperatorXNOR::getValue() const
{
    return this->left.get()->getValue() ==
            this->right.get()->getValue();
}
