#include "functionallowedrules.h"
#include "algorithm.h"
FunctionAllowedRules::FunctionAllowedRules(Algorithm * alg)
{
    this->algorithm = alg;
}
int FunctionAllowedRules::getValue() const
{
    return this->algorithm->getAmountOfAllowedEnvironsFunctions();
}
QString FunctionAllowedRules::reBuildStringFormula() const
{
    return "ALLOWED_FUNCTIONS";
}
