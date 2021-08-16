#include "valuevariable.h"
#include "parser.h"
ValueVariable::ValueVariable(QString iname, QString sformula, std::shared_ptr<ValueElement> iformula)
{
    this->name = iname;
    this->setFormula(sformula, iformula);
}
ValueVariable::~ValueVariable()
{

}


int ValueVariable::getValue() const
{
    return this->is_global ? this->single_value : this->values.getValue();
}

void ValueVariable::setFormula(QString sformula, std::shared_ptr<ValueElement> iformula)
{
    this->string_formula = sformula;
    this->formula = iformula;
    this->is_formula_valid = true;
}
QString ValueVariable::getStringFormula() const
{
    return this->string_formula;
}
void ValueVariable::setName(QString iname)
{
    this->name = iname;
}
void ValueVariable::setGlobality(bool iis_global)
{
    this->is_global = iis_global;
}
bool ValueVariable::isGlobal()
{
    return this->is_global;
}
QString ValueVariable::getName()
{
    return this->name;
}
QString ValueVariable::reBuildStringFormula() const
{
    return this->name;
}
void ValueVariable::buildStringFormula()
{
    if (this->is_formula_valid)
        this->string_formula = this->formula->reBuildStringFormula();
}
bool ValueVariable::isFormulaValid()
{
    return this->is_formula_valid;
}
void ValueVariable::reCompileFormula(Algorithm * alg, FieldDistributor * field)
{
    try {
        Parser parser(alg, field, this->is_global ? PARSER_MODE_GLOBAL_VARIABLE : PARSER_MODE_ITERATIVE_VARIABLE);
        parser.buildValueFormula(this->string_formula);
    } catch (QString exception) {

        if (is_formula_valid)
        {
            this->string_formula = "<недействительно> " + this->string_formula;
        }
        this->is_formula_valid = false;
    }
}
void ValueVariable::count()
{
    if (this->is_global)
        this->single_value = this->formula->getValue();
    else
        this->values.setValue(this->formula->getValue());
}
void ValueVariable::amountOfThreadsChanged(int new_amount)
{
    if (!this->is_global)
        this->values.setSize(new_amount);
}
