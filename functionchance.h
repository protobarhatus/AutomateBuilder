#ifndef FUNCTIONCHANCE_H
#define FUNCTIONCHANCE_H
#include"logicelement.h"
#include<memory>
class ValueElement;
class FunctionChance : public LogicElement
{
public:
    FunctionChance();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
    void setChance(std::shared_ptr<ValueElement> chance);
private:
    std::shared_ptr<ValueElement> chance;
};

#endif // FUNCTIONCHANCE_H
