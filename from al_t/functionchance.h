#ifndef FUNCTIONCHANCE_H
#define FUNCTIONCHANCE_H
#include"logicelement.h"

class FunctionChance : public LogicElement
{
public:
    FunctionChance();
    virtual bool getValue() const override;
private:
    unsigned char chance;
};

#endif // FUNCTIONCHANCE_H
