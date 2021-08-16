#include "actionsetbyf.h"
#include "algorithm.h"
#include "field.h"
#include "valueelement.h"
#include "somedataworks.h"
#include "fielddistributor.h"
ActionSetByF::ActionSetByF(Algorithm * ialgorithm, FieldDistributor * ifield)
{
    this->algorithm = ialgorithm;
    this->field = ifield;
}
void ActionSetByF::setStatementsNumber(std::shared_ptr<ValueElement> number)
{
    this->statements_number = number;
}
void ActionSetByF::doAction()
{
    Statement * statement = this->algorithm->getStatement(this->statements_number->getValue());
    //qDebug() << "the new statement is " << statement << " with number: " << statement->getNumber();
    if (statement)
        (*this->field)->setStatementToTheCurrent(statement);
}
QString ActionSetByF::getStringRepresentation()
{
    return "SET_BY_F " + getExpressionAsArgument(this->statements_number->reBuildStringFormula());
}
