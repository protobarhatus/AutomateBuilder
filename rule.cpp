#include "rule.h"
#include "logicelement.h"
#include "parser.h"
Rule::Rule()
{

}
void Rule::buildStringFormula()
{
    this->str_condition = this->condition->reBuildStringFormula();
    this->str_action = this->action.buildStringFormula();
    this->str_second_action = this->second_action.buildStringFormula();
    this->is_formula_valid = true;
}

void Rule::reCompileFormula(Algorithm * algorithm, FieldDistributor * field)
{
    try {
        Parser parser(algorithm, field, this->is_global ? PARSER_MODE_GLOBAL_RULES : PARSER_MODE_LOCAL_RULES);
        parser.buildLogicFormula(this->str_condition);
    } catch (QString exception) {
        if (this->is_formula_valid)
        {
            this->str_condition = "<недействительно> " + this->str_condition;
        }
        this->is_formula_valid = false;
        return;
    }
    if (!this->action.reCompileStringFormula(algorithm, field))
    {

        if (this->is_formula_valid)
        {
            //да, недействительно оказывается действие, а не условие. Однако они все равно визуализируются одной строкой,
            //а пометка "недействительно" может быть незаметна, если ставить ее после условия
            this->str_condition = "<недействительно> " + this->str_condition;
        }
        this->is_formula_valid = false;
    }
    if (!this->second_action.reCompileStringFormula(algorithm, field))
    {
        if (this->is_formula_valid)
        {
            this->str_condition = "<недействительно> " + this->str_second_action;
        }
        this->is_formula_valid = false;
    }
}
void Rule::complite()
{
    if (condition->getValue())
        this->action.doAction();
    else
        this->second_action.doAction();
}
void Rule::setCondition(QString str_cond, std::shared_ptr<LogicElement> icondition)
{
    this->str_condition = str_cond;
    this->condition = icondition;
}
void Rule::setAction(QString istr_action, std::shared_ptr<Action> iaction)
{
    this->str_action = istr_action;
    this->action = *iaction.get();
}
void Rule::setGlobality(bool iis_global)
{
    this->is_global = iis_global;
}
bool Rule::isGlobal()
{
    return this->is_global;
}
QString Rule::getStringRepresentation()
{
    return this->str_condition + " ? " + this->str_action + " : " + this->str_second_action;
}
QString Rule::getStringCondition()
{
    return this->str_condition;
}
QString Rule::getStringAction()
{
    return this->str_action;
}
QString Rule::getStringSecondAction()
{
    return this->str_second_action;
}
bool Rule::isFormulaValid()
{
    return this->is_formula_valid;
}
void Rule::setSecondAction(QString str_act, std::shared_ptr<Action> sec_action)
{
    this->str_second_action  = str_act;
    this->second_action = *sec_action.get();
}
