#ifndef FUNCTIONRAND_H
#define FUNCTIONRAND_H
#include"valueelement.h"

class FunctionRand : public ValueElement
{
public:
    FunctionRand();
    virtual int getValue() const override;
    void setLow(int low_border);
    void setHigh(int high_border);
private:
    int low;
    int high;
};

#endif // FUNCTIONRAND_H
