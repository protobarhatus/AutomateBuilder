#ifndef LOGICVALUE_H
#define LOGICVALUE_H
#include "logicelement.h"

class LogicValue : public LogicElement
{
public:
    LogicValue(bool value);
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
private:
    bool value;
};

#endif // LOGICVALUE_H
