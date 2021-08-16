#ifndef FUNCTIONRAND_H
#define FUNCTIONRAND_H
#include"valueelement.h"
#include "memory"
class FunctionRand : public ValueElement
{
public:
    FunctionRand();
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
    void setLow(std::shared_ptr<ValueElement> low_border);
    void setHigh(std::shared_ptr<ValueElement> high_border);
private:
    std::shared_ptr<ValueElement> low;
    std::shared_ptr<ValueElement> high;
};

#endif // FUNCTIONRAND_H
