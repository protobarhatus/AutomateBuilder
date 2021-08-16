#ifndef ACTIONSETBYF_H
#define ACTIONSETBYF_H
#include "actionelement.h"
#include "memory"

class ValueElement;
class Algorithm;
class FieldDistributor;

class ActionSetByF : public ActionElement
{
public:
    ActionSetByF(Algorithm * algorithm, FieldDistributor * field);
    void setStatementsNumber(std::shared_ptr<ValueElement> statements_number);

    virtual void doAction() override;
    virtual QString getStringRepresentation() override;

private:
    Algorithm * algorithm;
    FieldDistributor * field;
    std::shared_ptr<ValueElement> statements_number;
};

#endif // ACTIONSETBYF_H
