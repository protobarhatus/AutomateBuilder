#ifndef FUNCTIONALLOWEDRULES_H
#define FUNCTIONALLOWEDRULES_H
#include"valueelement.h"

class Algorithm;
class FunctionAllowedRules : public ValueElement
{
public:
    FunctionAllowedRules(Algorithm * algorithm);
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
    Algorithm * algorithm;
};

#endif // FUNCTIONALLOWEDRULES_H
