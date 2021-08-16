#ifndef RULE_H
#define RULE_H

#include<memory.h>
#include<action.h>
class LogicElement;
class Algorithm;
class FieldDistributor;

class Rule
{
public:
    Rule();
    void buildStringFormula();
    void reCompileFormula(Algorithm * algorithm, FieldDistributor * field);
    void complite();
    void setCondition(QString str_condition, std::shared_ptr<LogicElement> condition);
    void setAction(QString str_action, std::shared_ptr<Action> action);
    void setSecondAction(QString str_action, std::shared_ptr<Action> action);
    void setGlobality(bool is_global);
    bool isGlobal();
    QString getStringRepresentation();
    QString getStringCondition();
    QString getStringAction();
    QString getStringSecondAction();
    bool isFormulaValid();

private:

    std::shared_ptr<LogicElement> condition;
    Action action;
    //представляет else блок
    Action second_action;
    QString str_condition;
    QString str_action;
    QString str_second_action = "";
    bool is_global;
    bool is_formula_valid = true;
};

#endif // RULE_H
