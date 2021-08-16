#ifndef ARITHMETICALOPERATOR_H
#define ARITHMETICALOPERATOR_H
#include"valueelement.h"
#include"memory"
class ArithmeticalOperator : public ValueElement
{
public:
    ArithmeticalOperator();
    virtual int getValue() const = 0;
    virtual QString reBuildStringFormula() const = 0;
    void setLeftOperand(std::shared_ptr<ValueElement> l);
    void setRightOperand(std::shared_ptr<ValueElement> r);
protected:
    std::shared_ptr<ValueElement> left;
    std::shared_ptr<ValueElement> right;
};
class OperatorPlus : public ArithmeticalOperator
{
public:
    OperatorPlus();
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
};
class OperatorMinus : public ArithmeticalOperator
{
public:
    OperatorMinus();
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
};
class OperatorMultiplication : public ArithmeticalOperator
{
public:
    OperatorMultiplication();
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
};
class OperatorDivision : public ArithmeticalOperator
{
public:
    OperatorDivision();
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
};
class OperatorDivisionWithRounding : public ArithmeticalOperator
{
public:
    OperatorDivisionWithRounding();
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
};

class OperatorRemainder : public ArithmeticalOperator
{
public:
    OperatorRemainder();
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
};

#endif // ARITHMETICALOPERATOR_H
