#ifndef FUNCTIONCURRENTCELL_H
#define FUNCTIONCURRENTCELL_H
#include <valueelement.h>
class FieldDistributor;
class FunctionCurrentCell : public ValueElement
{
public:
    FunctionCurrentCell(FieldDistributor * field);
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;

private:
    FieldDistributor * field;
};

#endif // FUNCTIONCURRENTCELL_H
