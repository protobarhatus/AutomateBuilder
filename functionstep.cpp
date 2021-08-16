#include "functionstep.h"
#include "algorithm.h"
FunctionSTEP::FunctionSTEP(Algorithm * alg)
{
    this->algorithm = alg;
}
int FunctionSTEP::getValue() const
{
    return this->algorithm->getStep();
}
QString FunctionSTEP::reBuildStringFormula() const
{
    return "STEP";
}
