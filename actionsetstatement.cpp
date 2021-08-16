#include "actionsetstatement.h"
#include "statement.h"
#include "algorithm.h"
#include "fielddistributor.h"
#include "field.h"
ActionSetStatement::ActionSetStatement(FieldDistributor * ifield)
{
    this->field = ifield;
}
void ActionSetStatement::doAction()
{
    (*this->field)->setStatementToTheCurrent(this->statement);
}
QString ActionSetStatement::getStringRepresentation()
{
    return "SET \"" + this->statement->getName() + "\"";
}
void ActionSetStatement::setStatement(Statement * istatement)
{
    this->statement = istatement;
}
