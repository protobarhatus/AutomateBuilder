#ifndef FUNCTIONCONDINR_H
#define FUNCTIONCONDINR_H
#include<qstring.h>
#include"logicelement.h"
#include"wavefunction.h"
#include"memory"
class LogicValueOperator;
class ValueElement;
class FieldDistributor;
class Algorithm;
class FunctionCondInR : public LogicElement, public WaveFunction
{
public:
    FunctionCondInR(Algorithm * algorithm, FieldDistributor * field);
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
    void setLowBorder(std::shared_ptr<ValueElement> low);
    void setHighBorder(std::shared_ptr<ValueElement> high);
    void setOperator(std::shared_ptr<LogicValueOperator> oper);
    void setRightOperand(std::shared_ptr<ValueElement> right_operand);
private:
    std::shared_ptr<ValueElement> low_border;
    std::shared_ptr<ValueElement> high_border;
    std::shared_ptr<LogicValueOperator> v_operator;
    std::shared_ptr<ValueElement> right_operand;

};

#endif // FUNCTIONCONDINR_H
