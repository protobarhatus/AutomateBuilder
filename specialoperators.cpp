#include "specialoperators.h"
#include "statement.h"
#include "valueelement.h"

StatementsComparisonOperator::StatementsComparisonOperator()
{

}
bool StatementsComparisonOperator::getValue() const
{
    return this->left->getValue() == this->statement->getNumber();
}

QString StatementsComparisonOperator::reBuildStringFormula() const
{
    //this->left по определению является односложной функцией - это должен гарантировать парсер
    return this->left->reBuildStringFormula() + " = \"" + this->statement->getName() + "\"";
}
void StatementsComparisonOperator::setLeftOperand(std::shared_ptr<ValueElement> left_operand)
{
    this->left = left_operand;
}
void StatementsComparisonOperator::setRightOperand(Statement * istatement)
{
    this->statement = istatement;
}
