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
    void setRightOperand(std::shared_ptr<ValueElement>);
    void setLeftOperand(std::shared_ptr<ValueElement>);

protected:
    std::shared_ptr<ValueElement> left;
    std::shared_ptr<ValueElement> right;
};

class OperatorEquals : public LogicValueOperator
{
public:
    OperatorEquals();
    virtual bool getValue() const override;
};
class OperatorNotEquals : public LogicValueOperator
{
public:
    OperatorNotEquals();
    virtual bool getValue() const override;
};
class OperatorLess : public LogicValueOperator
{
public:
    OperatorLess();
    virtual bool getValue() const override;
};
class OperatorLessEquals : public LogicValueOperator
{
public:
    OperatorLessEquals();
    virtual bool getValue() const override;
};
class OperatorBigger : public LogicValueOperator
{
public:
    OperatorBigger();
    virtual bool getValue() const override;
};
class OperatorBiggerEquals : public LogicValueOperator
{
public:
    OperatorBiggerEquals();
    virtual bool getValue() const override;
};

#endif // LOGICVALUEOPERATOR_H
