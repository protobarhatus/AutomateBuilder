#ifndef FUNCTIONNOT_H
#define FUNCTIONNOT_H
#include "logicelement.h"
#include <memory>
class FunctionNot : public LogicElement
{
public:
    FunctionNot();
    void setExpression(std::shared_ptr<LogicElement> expression);
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;

private:
    std::shared_ptr<LogicElement> expression;
};

#endif // FUNCTIONNOT_H
