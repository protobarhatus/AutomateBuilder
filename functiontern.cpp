#include "functiontern.h"
#include "logicelement.h"
#include "somedataworks.h"
FunctionTern::FunctionTern()
{

}

int FunctionTern::getValue() const
{
    return this->condition->getValue() ? this->result_if_true->getValue() : this->result_if_false->getValue();
}
void FunctionTern::setCondition(std::shared_ptr<LogicElement> cond)
{
    this->condition = cond;
}
void FunctionTern::setResultIfTrue(std::shared_ptr<ValueElement> result)
{
    this->result_if_true = result;
}
void FunctionTern::setResultIfFalse(std::shared_ptr<ValueElement> result)
{
    this->result_if_false = result;
}
QString FunctionTern::reBuildStringFormula() const
{
    return "[TERN " + getExpressionAsArgument(this->condition->reBuildStringFormula()) + " Y " +
            getExpressionAsArgument(this->result_if_true->reBuildStringFormula()) + " N " +
            getExpressionAsArgument(this->result_if_false->reBuildStringFormula()) + "]";
}
