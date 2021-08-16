#ifndef VALUE_H
#define VALUE_H
#include"valueelement.h"

class Value : public ValueElement
{
public:
    Value(int value);
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
private:
    int value;
};

#endif // VALUE_H
