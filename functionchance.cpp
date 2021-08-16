#include "functionchance.h"
#include "random"
#include "valueelement.h"
#include "somedataworks.h"
FunctionChance::FunctionChance()
{

}
bool FunctionChance::getValue() const
{
    std::random_device rt;
     std::mt19937 gen(rt());
     std::uniform_int_distribution<int> dist(0, 99);
     return dist(gen) < this->chance->getValue();
}
void FunctionChance::setChance(std::shared_ptr<ValueElement> ch)
{
    this->chance = ch;
}
QString FunctionChance::reBuildStringFormula() const
{
    return "[CHANCE " + getExpressionAsArgument(this->chance->reBuildStringFormula()) + "]";
}
