#include "addenvironsfunctionformcontroller.h"
#include "ui_addenvironsfunctionform.h"
#include <QMessageBox>
#include "functioncell.h"
#include "somedataworks.h"
#include "controller.h"
#include "automate.h"
#include "algorithm.h"
AddEnvironsFunctionFormController::AddEnvironsFunctionFormController(Controller * icontroller, QString iname, int iX, int iY,
                                                                     bool iis_allowed) : form(this)
{
    this->controller = icontroller;
    this->name = iname;
    this->X = iX;
    this->Y = iY;
    this->is_allowed = iis_allowed;

    this->form.ui->NameLineEdit->setText(this->name);
    QString x_in_str, y_in_str;
    x_in_str.setNum(this->X);
    y_in_str.setNum(this->Y);
    this->form.ui->XLineEdit->setText(x_in_str);
    this->form.ui->YLineEdit->setText(y_in_str);
    this->form.ui->isAllowedCheckBox->setChecked(this->is_allowed);
}

void AddEnvironsFunctionFormController::start()
{
    this->form.exec();
}
bool AddEnvironsFunctionFormController::checkDataBeforeAccepting()
{
    if (!checkLineEditForDataPresense(this->form.ui->NameLineEdit, "имя", &this->form))
        return false;
    if (!this->form.ui->NameLineEdit->text().contains(QRegularExpression("^[A-ZА-Я_]+$")))
    {
        QMessageBox::information(&this->form, "Внимание", "Имя функции не соответствует шаблону. Имя функции может состоять \
из прописных букв английского и русского алфавита, а также знака нижнего подчеркивания.");
        return false;
    }
    if (this->name != this->form.ui->NameLineEdit->text() &&
            this->controller->getAutomate()->getAlgorithm()->hasEnvironsFunction(this->form.ui->NameLineEdit->text()))
    {
        QMessageBox::information(&this->form, "Внимание", "Функция окружения с таким именем уже существует.");
    }
    if (!isStringNumber(this->form.ui->XLineEdit->text()) ||
            !isStringNumber(this->form.ui->YLineEdit->text()))
    {
        QMessageBox::information(&this->form, "Внимание", "Координаты функции могут задаваться только числами");
        return false;
    }
    if (this->form.ui->XLineEdit->text().toInt() == 0 && this->form.ui->YLineEdit->text().toInt() == 0)
    {
        QMessageBox::information(&this->form, "Внимание", "Нельзя создать функцию окружения {0, 0}. Для получения состояния \
данной клетки используйте функцию CURRENT_CELL");
        return false;
    }
    return true;
}
void AddEnvironsFunctionFormController::closeWithAcceptingData()
{
    this->name = this->form.ui->NameLineEdit->text();
    this->X = this->form.ui->XLineEdit->text().toInt();
    this->Y = this->form.ui->YLineEdit->text().toInt();
    this->is_allowed = this->form.ui->isAllowedCheckBox->isChecked();
    this->isOK = true;
    this->form.close();
}
QString AddEnvironsFunctionFormController::getName()
{
    return this->name;
}
int AddEnvironsFunctionFormController::getX()
{
    return this->X;
}
int AddEnvironsFunctionFormController::getY()
{
    return this->Y;
}
bool AddEnvironsFunctionFormController::isAllowed()
{
    return this->is_allowed;
}
bool AddEnvironsFunctionFormController::isOk()
{
    return this->isOK;
}
