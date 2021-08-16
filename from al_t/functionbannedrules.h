#ifndef FUNCTIONBANNEDRULES_H
#define FUNCTIONBANNEDRULES_H
#include"valueelement.h"
class AlgorithmInterface;

class FunctionBannedRules : public ValueElement
{
public:
    FunctionBannedRules();
    virtual int getValue() const override;

private:
    AlgorithmInterface * algorithm;
};

#endif // FUNCTIONBANNEDRULES_H
