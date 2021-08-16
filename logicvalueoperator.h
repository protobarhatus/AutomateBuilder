#ifndef LOGICVALUEOPERATOR_H
#define LOGICVALUEOPERATOR_H
#include "logicelement.h"
#include <memory>
class ValueElement;
class LogicValueOperator : public LogicElement
{
public:
    LogicValueOperator();
    virtual bool getValue() const = 0;
    virtual QString reBuildStringFormula() const = 0;
    virtual QString getStringRepresentation() = 0;
    void setRightOperand(std::shared_ptr<ValueElement>);
    void setLeftOperand(std::shared_ptr<ValueElement>);
    virtual bool setLeftOperandAndCompute(int left) = 0;

protected:
    std::shared_ptr<ValueElement> left;
    std::shared_ptr<ValueElement> right;
};

class OperatorEquals : public LogicValueOperator
{
public:
    OperatorEquals();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
    virtual QString getStringRepresentation() override;
    virtual bool setLeftOperandAndCompute(int left) override;
};
class OperatorNotEquals : public LogicValueOperator
{
public:
    OperatorNotEquals();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
    virtual QString getStringRepresentation() override;
    virtual bool setLeftOperandAndCompute(int left) override;
};
class OperatorLess : public LogicValueOperator
{
public:
    OperatorLess();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
    virtual QString getStringRepresentation() override;
    virtual bool setLeftOperandAndCompute(int left) override;
};
class OperatorLessEquals : public LogicValueOperator
{
public:
    OperatorLessEquals();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
    virtual QString getStringRepresentation() override;
    virtual bool setLeftOperandAndCompute(int left) override;
};
class OperatorBigger : public LogicValueOperator
{
public:
    OperatorBigger();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
    virtual QString getStringRepresentation() override;
    virtual bool setLeftOperandAndCompute(int left) override;
};
class OperatorBiggerEquals : public LogicValueOperator
{
public:
    OperatorBiggerEquals();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
    virtual QString getStringRepresentation() override;
    virtual bool setLeftOperandAndCompute(int left) override;
};

#endif // LOGICVALUEOPERATOR_H
