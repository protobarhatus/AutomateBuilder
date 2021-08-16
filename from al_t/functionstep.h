#ifndef FUNCTIONSTEP_H
#define FUNCTIONSTEP_H
#include"valueelement.h"
class FieldInterface;
class FunctionSTEP : public ValueElement
{
public:
    FunctionSTEP();
    virtual int getValue() const override;

private:
    FieldInterface * field;
};

#endif // FUNCTIONSTEP_H
