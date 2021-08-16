#ifndef FUNCTIONCOUNT_H
#define FUNCTIONCOUNT_H
#include"valueelement.h"
#include"wavefunction.h"
#include<memory>
#include<vector>
class LogicValueOperator;
class FieldDistributor;
class Algorithm;
class FunctionCell;

class FunctionCount : public ValueElement, public WaveFunction
{
public:
    FunctionCount(Algorithm * algorithm, FieldDistributor * field);
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;

    void setOperator(std::shared_ptr<LogicValueOperator> v_operator);
    void setRightOperand(std::shared_ptr<ValueElement> right_operand);
private:

    std::shared_ptr<LogicValueOperator> v_operator;
    std::shared_ptr<ValueElement> right_operand;


};

#endif // FUNCTIONCOUNT_H
