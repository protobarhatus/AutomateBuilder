#include "addruleformcontroller.h"
#include "ui_addruleform.h"
#include "parser.h"
#include "controller.h"
#include "automate.h"
#include "QMessageBox"
AddRuleFormController::AddRuleFormController(Controller * controller,
    QString icondition, QString iaction, QString istr_sec_action, bool iis_global) :
    form(this, icondition, iaction, istr_sec_action, iis_global)
{
    this->controller = controller;
    this->str_condition = icondition;
    this->str_action = iaction;
    this->str_second_action = istr_sec_action;
    this->is_global = iis_global;
}
void AddRuleFormController::start()
{
    this->form.exec();
}

bool AddRuleFormController::checkDataBeforeAccepting()
{
    Parser parser(this->controller->getAutomate()->getAlgorithm(),
                  this->controller->getAutomate()->getField(),
                  this->form.ui->isGlobalRadioButton->isChecked() ?
                      PARSER_MODE_GLOBAL_RULES : PARSER_MODE_LOCAL_RULES);
    try {
        this->condition = parser.buildLogicFormula(this->form.ui->ConditionLineEdit->text());
        this->action = parser.buildAction(this->form.ui->ActionLineEdit->text());
        this->second_action = parser.buildAction(this->form.ui->elseLineEdit->text());
        return true;
    } catch (QString exception) {
        QMessageBox::information(&this->form, "Ошибка", exception);
        return false;
    }
}
void AddRuleFormController::closeWithAcceptingData()
{
    this->str_condition = this->form.ui->ConditionLineEdit->text();
    this->str_action = this->form.ui->ActionLineEdit->text();
    this->str_second_action = this->form.ui->elseLineEdit->text();
    this->is_global = this->form.ui->isGlobalRadioButton->isChecked();
    this->is_OK = true;
    this->form.close();
}

QString AddRuleFormController::getStrCondition()
{
    return this->str_condition;
}
QString AddRuleFormController::getStrAction()
{
    return this->str_action;
}
bool AddRuleFormController::isGlobal()
{
    return this->is_global;
}
bool AddRuleFormController::isOK()
{
    return this->is_OK;
}
std::shared_ptr<LogicElement> AddRuleFormController::getCondition()
{
    return this->condition;
}
std::shared_ptr<Action> AddRuleFormController::getAction()
{
    return this->action;
}
QString AddRuleFormController::getStrSecondAction()
{
    return this->str_second_action;
}
std::shared_ptr<Action> AddRuleFormController::getSecondAction()
{
    return this->second_action;
}
