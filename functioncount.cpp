#include "functioncount.h"
#include "logicvalueoperator.h"
#include "somedataworks.h"
#include "field.h"
#include "algorithm.h"
#include "value.h"
#include <QMutex>
#include "thread.h"
FunctionCount::FunctionCount(Algorithm * ialgorithm, FieldDistributor * ifield) : WaveFunction (ialgorithm, ifield)
{

}
int FunctionCount::getValue() const
{
    int amount_of_right_statements = 0;
    for (auto it : this->environs_functions)
    {       
        if (v_operator->setLeftOperandAndCompute(it->getValue()))
        {
            ++amount_of_right_statements;
        }
    }
    return amount_of_right_statements;
}

void FunctionCount::setOperator(std::shared_ptr<LogicValueOperator> oper)
{
    this->v_operator = oper;
    if (this->right_operand.get() != nullptr)
        this->v_operator->setRightOperand(this->right_operand);
}
void FunctionCount::setRightOperand(std::shared_ptr<ValueElement> iright_operand)
{
    this->right_operand = iright_operand;
    if (this->v_operator.get() != nullptr)
        this->v_operator->setRightOperand(this->right_operand);
}
QString FunctionCount::reBuildStringFormula() const
{
    return "[COUNT " + getExpressionAsArgument(this->radius->reBuildStringFormula()) + " " +
            this->v_operator->getStringRepresentation() + " " +
            getExpressionAsArgument(this->right_operand->reBuildStringFormula()) + "]";
}
