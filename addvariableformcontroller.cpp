#include "addvariableformcontroller.h"
#include "ui_addvariableform.h"
#include <QMessageBox>
#include "somedataworks.h"
#include "controller.h"
#include "QDebug"
#include "parser.h"
#include "algorithm.h"
#include "automate.h"
#include "field.h"
AddVariableFormController::AddVariableFormController(Controller * controller, Automate * iautomate)
{
    this->main_controller = controller;
    this->automate = iautomate;
}
void AddVariableFormController::start(QString iname, QString str_value, VariableType itype, VariableClass iclass)
{
    this->form.reset(new AddVariableForm(this, iname, itype, iclass));
    this->form->ui->ValueLineEdit->setText(str_value);
    this->name = iname;
    this->form->exec();

}

void AddVariableFormController::closeWithAcceptingData()
{
    this->dialog_result = true;

        this->name = this->form->ui->NameEdit->text();
        this->type = this->form->ui->isLogicRadioButton->isChecked() ? LOGIC : VALUE;
        this->formula = this->form->ui->ValueLineEdit->text();
        this->v_class = this->form->ui->isGlobalRadioButton->isChecked() ? GLOBAL : ITERATIVE;


        this->form->close();

}
bool AddVariableFormController::isOK()
{
    return this->dialog_result;
}
bool AddVariableFormController::checkDataBeforeAccepting()
{

    AddVariableForm * form_pointer = this->form.get();
    if (!checkLineEditForDataPresense(this->form->ui->NameEdit, "имя переменной", form_pointer))
        return false;
    if (!Automate::isVariableNameCorrectlyWritten(this->form->ui->NameEdit->text()))
    {
        QMessageBox::information(form_pointer, "Внимание!", "Имя переменной записано некорректно. Имя должно начинаться с \
буквы русского или английского алфавита и состоять из букв, цифр или знаков нижнего подчеркивания, а также должно иметь хотя \
бы одну букву нижнего регистра или цифру.");
        return false;
    }
    if (!checkLineEditForDataPresense(this->form->ui->ValueLineEdit, "значение", form_pointer))
        return false;
    if (this->form->ui->NameEdit->text() != this->name && !this->main_controller->isVariablesNameFree(this->form->ui->NameEdit->text(),
                                                    this->form->ui->isLogicRadioButton->isChecked() ? ITERATIVE :
                                                    this->form->ui->isIterativeRadioButton->isChecked() ? ITERATIVE : GLOBAL))
    {
        QMessageBox::information(form_pointer, "Внимание!", "Переменная с именем \"" +
                                 this->form->ui->NameEdit->text() + "\" уже существует.");
        return false;
    }
    if (this->form->ui->isLogicRadioButton->isChecked())
    {
        return tryToBuildLogicFormula(this->form->ui->ValueLineEdit->text());
    }
    else
    {
        return tryToBuildNumericFormula(this->form->ui->ValueLineEdit->text());
    }

}
QString AddVariableFormController::getName()
{
    return this->name;
}
VariableType AddVariableFormController::getType()
{
    return this->type;
}
VariableClass AddVariableFormController::getClass()
{
    return this->v_class;
}
std::shared_ptr<LogicElement> AddVariableFormController::getLogicValue()
{
    return this->logic_value;
}
std::shared_ptr<ValueElement> AddVariableFormController::getNumericValue()
{
    return this->numeric_value;
}
bool AddVariableFormController::tryToBuildLogicFormula(QString formula)
{

    try {
        ParserMode mode = this->form->ui->isGlobalRadioButton->isChecked() ? PARSER_MODE_GLOBAL_VARIABLE :
                                                                             PARSER_MODE_ITERATIVE_VARIABLE;
        Parser parser(this->automate->getAlgorithm(), this->automate->getField(), mode);
        this->logic_value = parser.buildLogicFormula(formula);
        return true;
    } catch (QString exception) {
        QMessageBox::information(this->form.get(), "Ошибка", exception);
        return false;
    }
}
bool AddVariableFormController::tryToBuildNumericFormula(QString formula)
{
    try {
        ParserMode mode = this->form->ui->isGlobalRadioButton->isChecked() ? PARSER_MODE_GLOBAL_VARIABLE :
                                                                             PARSER_MODE_ITERATIVE_VARIABLE;
        Parser parser(this->automate->getAlgorithm(), this->automate->getField(), mode);
        this->numeric_value = parser.buildValueFormula(formula);
        return true;
    } catch (QString exception) {
        QMessageBox::information(this->form.get(), "Ошибка", exception);
        return false;
    }
}
QString AddVariableFormController::getFormula()
{
    return this->formula;
}
