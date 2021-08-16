#include "functionslcount.h"
#include "logicvalueoperator.h"
#include "somedataworks.h"
#include "field.h"
#include "algorithm.h"
#include "value.h"
#include "fielddistributor.h"
FunctionSlCount::FunctionSlCount(Algorithm * ialgorithm, FieldDistributor * ifield)
{
    this->algorithm = ialgorithm;
    this->field = ifield;
}
int FunctionSlCount::getValue() const
{
    int amount_of_right_statements = 0;
    (*this->field)->doWaveRelativelyToTheCurrent<int>(this->algorithm->getAllowedEnvironsFunctions(), this->rad->getValue(),
                                              [this](Statement * statement, int * params) {
        //qDebug() << "\t\t\t\t" << statement->getName();
        if (this->v_operator->setLeftOperandAndCompute(statement->getNumber()))
        {
            ++(*params);
            //qDebug() << "\t\t\t\tcredited, new amount: " << *params;
        }
    }, &amount_of_right_statements );
    //qDebug() << "\tRESULT: " << amount_of_right_statements << "\n}\n";
    return amount_of_right_statements;
}
void FunctionSlCount::setRadius(std::shared_ptr<ValueElement> radius)
{
    this->rad = radius;
}
void FunctionSlCount::setOperator(std::shared_ptr<LogicValueOperator> oper)
{
    this->v_operator = oper;
    if (this->right_operand.get() != nullptr)
        this->v_operator->setRightOperand(this->right_operand);
}
void FunctionSlCount::setRightOperand(std::shared_ptr<ValueElement> iright_operand)
{
    this->right_operand = iright_operand;
    if (this->v_operator.get() != nullptr)
        this->v_operator->setRightOperand(this->right_operand);
}
QString FunctionSlCount::reBuildStringFormula() const
{
    return "[COUNT " + getExpressionAsArgument(this->rad->reBuildStringFormula()) + " " +
            this->v_operator->getStringRepresentation() + " " +
            getExpressionAsArgument(this->right_operand->reBuildStringFormula()) + "]";
}
