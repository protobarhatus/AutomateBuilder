#ifndef VALUEELEMENT_H
#define VALUEELEMENT_H
#include <QString>

class ValueElement
{
public:
    ValueElement();

    virtual int getValue() const = 0;
    virtual QString reBuildStringFormula() const = 0;
    virtual ~ValueElement();

};

#endif // VALUEELEMENT_H
