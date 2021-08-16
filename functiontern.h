#ifndef FUNCTIONTERN_H
#define FUNCTIONTERN_H
#include "valueelement.h"
#include "memory"
class LogicElement;

class FunctionTern : public ValueElement
{
public:
    FunctionTern();
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
    void setCondition(std::shared_ptr<LogicElement> condition);
    void setResultIfTrue(std::shared_ptr<ValueElement> result);
    void setResultIfFalse(std::shared_ptr<ValueElement> result);
private:
    std::shared_ptr<LogicElement> condition;
    std::shared_ptr<ValueElement> result_if_true;
    std::shared_ptr<ValueElement> result_if_false;
};

#endif // FUNCTIONTERN_H
