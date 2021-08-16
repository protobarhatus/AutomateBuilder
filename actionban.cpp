#include "actionban.h"
#include "algorithm.h"
ActionBan::ActionBan(Algorithm * ialgorithm)
{
    this->algorithm = ialgorithm;
}
void ActionBan::doAction()
{
    this->algorithm->banEnvironsFunction(this->function->getName());
}
QString ActionBan::getStringRepresentation()
{
    return "BAN " + this->function->getName();
}
void ActionBan::setFunction(FunctionCell * ifunction)
{
    this->function = ifunction;
}
