#ifndef ACTIONBAN_H
#define ACTIONBAN_H
#include "actionelement.h"
class Algorithm;
class FunctionCell;
class ActionBan : public ActionElement
{
public:
    ActionBan(Algorithm * algorithm);
    virtual void doAction() override;
    virtual QString getStringRepresentation() override;
    void setFunction(FunctionCell * function);

private:
    FunctionCell * function;
    Algorithm * algorithm;
};

#endif // ACTIONBAN_H
