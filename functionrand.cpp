#include "functionrand.h"
#include<random>
#include "somedataworks.h"
#include "QDebug"
#include "time.h"
#include <random>
FunctionRand::FunctionRand()
{

}
void FunctionRand::setHigh(std::shared_ptr<ValueElement> high_border)
{
    this->high = high_border;
}
void FunctionRand::setLow(std::shared_ptr<ValueElement> low_border)
{
    this->low = low_border;
}
int FunctionRand::getValue() const
{
    int max = this->high->getValue();
    int min = this->low->getValue();

   std::random_device rt;
    std::mt19937 gen(rt());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(rt);
}
QString FunctionRand::reBuildStringFormula() const
{
    return "[RAND " + getExpressionAsArgument(this->low->reBuildStringFormula()) + " TO " +
            getExpressionAsArgument(this->high->reBuildStringFormula()) + "]";
}
