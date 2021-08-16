#include "actionallow.h"
#include "algorithm.h"

ActionAllow::ActionAllow(Algorithm * ialgorithm)
{
    this->algorithm = ialgorithm;
}
void ActionAllow::doAction()
{
    this->algorithm->allowEnvironsFunction(this->function->getName());
}
QString ActionAllow::getStringRepresentation()
{
    return "ALLOW " + this->function->getName();
}
void ActionAllow::setFunction(FunctionCell * ifunction)
{
    this->function = ifunction;
}
