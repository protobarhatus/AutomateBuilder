#include "functionbannedrules.h"
#include "algorithm.h"
FunctionBannedRules::FunctionBannedRules(Algorithm * ialgorithm)
{
    this->algorithm = ialgorithm;
}
int FunctionBannedRules::getValue() const
{
    return this->algorithm->getAmountOfBannedEnvironsFunctions();
}
QString FunctionBannedRules::reBuildStringFormula() const
{
    return "BANNED_FUNCTIONS";
}
