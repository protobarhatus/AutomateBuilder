#ifndef FUNCTIONBANNEDRULES_H
#define FUNCTIONBANNEDRULES_H
#include"valueelement.h"
class Algorithm;
class FunctionBannedRules : public ValueElement
{
public:
    FunctionBannedRules(Algorithm * algorithm);
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
private:
    Algorithm * algorithm;
};

#endif // FUNCTIONBANNEDRULES_H
