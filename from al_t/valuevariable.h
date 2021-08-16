#ifndef VALUEVARIABLE_H
#define VALUEVARIABLE_H
#include<QString>
#include"valueelement.h"

class ValueVariable : public ValueElement
{
public:
    ValueVariable(QString name, int value);
    virtual int getValue() const override;
    ValueVariable(QString name);
    ~ValueVariable() override;
private:
    QString name;
    int value;
};

#endif // VALUEVARIABLE_H
