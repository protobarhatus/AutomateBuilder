#include "functioncondinr.h"
#include "valueelement.h"
#include "logicvalueoperator.h"
#include "somedataworks.h"
#include "field.h"
#include "algorithm.h"
#include "value.h"
FunctionCondInR::FunctionCondInR(Algorithm * alg, FieldDistributor * ifield) : WaveFunction (alg, ifield)
{

}
bool FunctionCondInR::getValue() const
{
    int amount_of_right_statements = 0;
    for (auto &it: this->environs_functions)
    {
        if (v_operator->setLeftOperandAndCompute(it->getValue()))
            ++amount_of_right_statements;
    }
    return amount_of_right_statements >= this->low_border->getValue() &&
            amount_of_right_statements <= this->high_border->getValue();
}

void FunctionCondInR::setLowBorder(std::shared_ptr<ValueElement> low)
{
    this->low_border = low;
}
void FunctionCondInR::setHighBorder(std::shared_ptr<ValueElement> high)
{
    this->high_border = high;
}
void FunctionCondInR::setOperator(std::shared_ptr<LogicValueOperator> oper)
{
    this->v_operator = oper;
    if (this->right_operand.get() != nullptr)
        this->v_operator->setRightOperand(this->right_operand);
}
void FunctionCondInR::setRightOperand(std::shared_ptr<ValueElement> right)
{
    this->right_operand = right;
    if (this->v_operator.get() != nullptr)
        this->v_operator->setRightOperand(right);
}
QString FunctionCondInR::reBuildStringFormula() const
{
    return "[COND_IN_R " + getExpressionAsArgument(this->radius->reBuildStringFormula()) + " FR " +
            getExpressionAsArgument(this->low_border->reBuildStringFormula()) + " TO " +
            getExpressionAsArgument(this->high_border->reBuildStringFormula()) +
            " " + this->v_operator->getStringRepresentation() + " " +
            getExpressionAsArgument(this->right_operand->reBuildStringFormula()) + "]";
}
