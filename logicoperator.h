#ifndef LOGICOPERATOR_H
#define LOGICOPERATOR_H
#include"logicelement.h"
#include<memory>
class LogicOperator : public LogicElement
{
public:
    LogicOperator();
    void setLeftOperand(std::shared_ptr<LogicElement> l);
    void setRightOperand(std::shared_ptr<LogicElement> r);
    virtual bool getValue() const = 0;
    virtual QString reBuildStringFormula() const = 0;

protected:
    std::shared_ptr<LogicElement> left;
    std::shared_ptr<LogicElement> right;
};

class OperatorAND : public LogicOperator
{
public:
    OperatorAND();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
};

class OperatorOR : public LogicOperator
{
public:
    OperatorOR();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
};

class OperatorNAND : public LogicOperator
{
public:
    OperatorNAND();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
};

class OperatorNOR : public LogicOperator
{
public:
    OperatorNOR();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
};

class OperatorXOR : public LogicOperator
{
public:
    OperatorXOR();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
};

class OperatorXNOR : public LogicOperator
{
public:
    OperatorXNOR();
    virtual bool getValue() const override;
    virtual QString reBuildStringFormula() const override;
};

#endif // LOGICOPERATOR_H
