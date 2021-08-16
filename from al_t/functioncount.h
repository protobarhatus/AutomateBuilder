#ifndef FUNCTIONCOUNT_H
#define FUNCTIONCOUNT_H
#include"valueelement.h"
#include<memory>
class LogicValueOperator;
class FieldInterface;

class FunctionCount : public ValueElement
{
public:
    FunctionCount();
    virtual int getValue() const override;


private:
    int rad;
    std::shared_ptr<LogicValueOperator> v_operator;
    std::shared_ptr<ValueElement> right_operand;
    FieldInterface * field;
};

#endif // FUNCTIONCOUNT_H
