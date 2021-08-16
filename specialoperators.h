#ifndef SPECIALOPERATORS_H
#define SPECIALOPERATORS_H
#include "logicelement.h"
#include <memory>
class ValueElement;
class Statement;

class StatementsComparisonOperator : public LogicElement
{
public:
    StatementsComparisonOperator();
    virtual bool getValue() const override;

    virtual QString reBuildStringFormula() const override;
    //парсер должен гарантировать, что operand является функцией окружения или CURRENT_CELL. Класс за это не отвечает
    void setLeftOperand(std::shared_ptr<ValueElement> operand);
    void setRightOperand(Statement * statement);

private:
    std::shared_ptr<ValueElement> left;
    Statement * statement;
};


#endif // SPECIALOPERATORS_H
