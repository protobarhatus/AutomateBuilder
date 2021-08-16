#ifndef FUNCTIONSTEP_H
#define FUNCTIONSTEP_H
#include"valueelement.h"
class Algorithm;
class FunctionSTEP : public ValueElement
{
public:
    FunctionSTEP(Algorithm * algorithm);
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
private:
    Algorithm * algorithm;
};

#endif // FUNCTIONSTEP_H
