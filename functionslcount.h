#ifndef FUNCTIONSLCOUNT_H
#define FUNCTIONSLCOUNT_H
#include"valueelement.h"
#include<memory>
#include<vector>
class LogicValueOperator;
class FieldDistributor;
class Algorithm;
class FunctionCell;
class FunctionSlCount : public ValueElement
{
public:
    FunctionSlCount(Algorithm * algorithm, FieldDistributor * field);
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
    void setRadius(std::shared_ptr<ValueElement> radius);
    void setOperator(std::shared_ptr<LogicValueOperator> v_operator);
    void setRightOperand(std::shared_ptr<ValueElement> right_operand);
private:
    std::shared_ptr<ValueElement> rad;
    std::shared_ptr<LogicValueOperator> v_operator;
    std::shared_ptr<ValueElement> right_operand;
    FieldDistributor * field;
    Algorithm * algorithm;

};
#endif // FUNCTIONSLCOUNT_H
