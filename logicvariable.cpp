#include "logicvariable.h"
#include "parser.h"
LogicVariable::LogicVariable(QString iname, QString sformula, std::shared_ptr<LogicElement> iformula)
{
    this->name = iname;
    this->setFormula(sformula, iformula);
}
LogicVariable::LogicVariable(QString iname)
{
    this->name = iname;
}
bool LogicVariable::getValue() const
{
    return this->is_global ? single_value : this->values.getValue();
}

bool operator<(LogicVariable left, LogicVariable right)
{
    return left.name < right.name;
}
void LogicVariable::setFormula(QString sformula, std::shared_ptr<LogicElement> iformula)
{
    this->formula = iformula;
    this->string_formula = sformula;
    this->is_formula_valid = true;
}
QString LogicVariable::getStringFormula() const
{
    return this->string_formula;
}
void LogicVariable::setName(QString iname)
{
    this->name = iname;
}
void LogicVariable::setGlobality(bool iis_global)
{
    this->is_global = iis_global;
}
bool LogicVariable::isGlobal()
{
    return this->is_global;
}
QString LogicVariable::getName()
{
    return this->name;
}
QString LogicVariable::reBuildStringFormula() const
{
    return this->name;
}
void LogicVariable::buildStringFormula()
{
    if (is_formula_valid)
        this->string_formula = this->formula->reBuildStringFormula();
}
bool LogicVariable::isFormulaValid()
{
    return this->is_formula_valid;
}
void LogicVariable::reCompileFormula(Algorithm * alg, FieldDistributor * field)
{
    try {
        Parser parser(alg, field, this->is_global ? PARSER_MODE_GLOBAL_VARIABLE : PARSER_MODE_ITERATIVE_VARIABLE);
        parser.buildLogicFormula(this->string_formula);
    } catch (QString exception) {

        if (is_formula_valid)
        {
            this->string_formula = "<недействительно> " + this->string_formula;
        }
        this->is_formula_valid = false;
    }
}
void LogicVariable::count()
{
    //qDebug() << is_global;
    if (this->is_global)
        this->single_value = this->formula->getValue();
    else
        this->values.setValue(this->formula->getValue());
}
void LogicVariable::amountOfThreadsChanged(int new_amount)
{
    if (!this->is_global)
        this->values.setSize(new_amount);
}
