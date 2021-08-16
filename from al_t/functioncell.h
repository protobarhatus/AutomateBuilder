#ifndef FUNCTIONCELL_H
#define FUNCTIONCELL_H
#include"valueelement.h"

class Field;
class FunctionCell : public ValueElement
{
public:
    FunctionCell();
    virtual int getValue() const override;

private:
    int X, Y;
    Field * field;
};

#endif // FUNCTIONCELL_H
