#ifndef FUNCTIONCONDINR_H
#define FUNCTIONCONDINR_H
#include<qstring.h>
#include"logicelement.h"
#include"memory"
class LogicValueOperator;
class ValueElement;
class FieldInterface;
class FunctionCondInR : public LogicElement
{
public:
    FunctionCondInR();
    //not defined
    virtual bool getValue() const override;

private:
    unsigned char R;
    short int low_border;
    short int high_border;
    std::shared_ptr<LogicValueOperator> v_operator;
    std::shared_ptr<ValueElement> right_operand;
    //this field lifetime is controlling by Controller class, so I can don't use smart pointers
    FieldInterface * field;
};

#endif // FUNCTIONCONDINR_H
