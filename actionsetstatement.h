#ifndef ACTIONSETSTATEMENT_H
#define ACTIONSETSTATEMENT_H
#include "actionelement.h"
class Statement;
class Algorithm;
class FieldDistributor;

class ActionSetStatement : public ActionElement
{
public:
    ActionSetStatement(FieldDistributor * field);
    virtual void doAction() override;
    virtual QString getStringRepresentation() override;
    void setStatement(Statement * statement);

private:
    Statement * statement;
    FieldDistributor * field;

};

#endif // ACTIONSETSTATEMENT_H
