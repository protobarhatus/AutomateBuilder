#ifndef RULE_H
#define RULE_H
#include<valuevariable.h>
#include<logicvariable.h>
#include<vector>
#include<action.h>
class LogicElement;
class Rule
{
public:
    Rule();
    typedef std::vector<ValueVariable> valueConstantList;
    typedef std::vector<LogicVariable> logicConstantList;
    void setRule(QString str_rule);
private:
    valueConstantList value_constants;
    logicConstantList logic_constants;
    LogicElement * condition;
    Action action;


};

#endif // RULE_H
