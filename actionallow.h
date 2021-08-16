#ifndef ACTIONALLOW_H
#define ACTIONALLOW_H
#include "actionelement.h"
class Algorithm;
class FunctionCell;

class ActionAllow : public ActionElement
{
public:
    ActionAllow(Algorithm * algorithm);
    virtual void doAction() override;
    virtual QString getStringRepresentation() override;
    void setFunction(FunctionCell * function);

private:
    FunctionCell * function;
    Algorithm * algorithm;
};

#endif // ACTIONALLOW_H
