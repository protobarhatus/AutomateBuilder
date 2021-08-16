#ifndef ACTIONELEMENT_H
#define ACTIONELEMENT_H
#include <QString>

class ActionElement
{
public:
    ActionElement();
    virtual ~ActionElement();
    virtual void doAction() = 0;
    virtual QString getStringRepresentation() = 0;
};

#endif // ACTIONELEMENT_H
