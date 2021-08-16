#include "action.h"
#include "actionelement.h"
#include "parser.h"
Action::Action()
{

}
void Action::addActionElement(std::shared_ptr<ActionElement> action_element, QString string_action_element)
{
    this->action_elements.push_back(action_element);
    this->string_formula = string_action_element;
}
void Action::doAction()
{
    for (auto &it : action_elements)
    {
        it->doAction();
    }
}
QString Action::buildStringFormula()
{
    this->string_formula = "";
    if (this->action_elements.empty())
        return "";
    this->string_formula = this->action_elements[0]->getStringRepresentation();
    for (auto &it = ++this->action_elements.begin(); it != this->action_elements.end(); ++it)
    {
        this->string_formula += " & " + it->get()->getStringRepresentation();
    }
    return this->string_formula;
}

bool Action::reCompileStringFormula(Algorithm * algorithm, FieldDistributor * field)
{

    try {
        Parser parser(algorithm, field, PARSER_MODE_LOCAL_RULES);
        parser.buildAction(this->string_formula);
        return true;
    } catch (QString exception) {

        return false;
    }
}
QString Action::getStringFormula()
{
    return this->string_formula;
}
