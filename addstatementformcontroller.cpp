#include "addstatementformcontroller.h"
#include "ui_addstatementform.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QRgba64>
#include "somedataworks.h"
#include "controller.h"
#include "automate.h"
#include "algorithm.h"
AddStatementFormController::AddStatementFormController(Controller * controller, QString iname, int inumber) : form(this)
{
    this->name = iname;
    this->number = inumber;
    this->has_defined_number = true;
    this->form.ui->NameLineEdit->setText(iname);
    QString number_in_string;
    number_in_string.setNum(inumber);
    this->form.ui->NumberLineEdit->setText(number_in_string);
    this->main_controller = controller;
}
AddStatementFormController::AddStatementFormController(Controller * controller) : form(this)
{
    this->name = "";
    this->number = 0;
    this->has_defined_number = false;
    this->form.ui->NameLineEdit->setText(this->name);
    QString number_in_string;
    number_in_string.setNum(this->number);
    this->form.ui->NumberLineEdit->setText(number_in_string);
    this->main_controller = controller;
}
void AddStatementFormController::setColor(QColor icolor)
{
    this->color = icolor;
    QPixmap pixmap(this->form.ui->ImageLabel->width(), this->form.ui->ImageLabel->height());
    pixmap.fill(icolor);
    this->form.ui->ImageLabel->setPixmap(pixmap);
    this->is_given_by_color = true;
    this->has_choosen_representation = true;
}
void AddStatementFormController::setImage(QPixmap pixmap)
{
    this->is_given_by_color = false;
    this->form.ui->ImageLabel->setPixmap(pixmap.scaled(this->form.ui->ImageLabel->width(),
                                                       this->form.ui->ImageLabel->height()));
    this->image = pixmap;
    this->has_choosen_representation = true;
}
void AddStatementFormController::start()
{
    this->form.exec();
}
void AddStatementFormController::loadImageButtonPressed()
{
    QString file_name = QFileDialog::getOpenFileName(&this->form,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Images (*.png *.jpg *.bmp *.gif *.jpeg)");
    if (file_name.isEmpty())
        return;
    this->setImage(QPixmap(file_name));
}
void AddStatementFormController::changeColorButtonPressed()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid())
    {
        this->setColor(color);
    }
}
bool AddStatementFormController::checkDataBeforeAccepting()
{
    if (!checkLineEditForDataPresense(this->form.ui->NameLineEdit, "имя состояния", &this->form))
        return false;
    if (this->name != this->form.ui->NameLineEdit->text() &&
            this->main_controller->getAutomate()->getAlgorithm()->hasStatement(this->form.ui->NameLineEdit->text()))
    {
        QMessageBox::information(&this->form, "Внимание", "Состояние с данным именем уже существует");
        return false;
    }
    if (!checkForConsistingOfOneWord(this->form.ui->NameLineEdit, "имя состояния", &this->form))
        return false;
    if (!checkLineEditForDataPresense(this->form.ui->NumberLineEdit, "номер состояния", &this->form))
        return false;
    if (!checkForNumber(this->form.ui->NumberLineEdit, "номер состояния", &this->form))
        return false;
    if (this->main_controller->getAutomate()->getAlgorithm()->hasStatement(this->form.ui->NumberLineEdit->text().toInt()) &&
            (!this->has_defined_number ||
            (this->form.ui->NumberLineEdit->text().toInt() != this->number && this->has_defined_number)))
    {
        QMessageBox::information(&this->form, "Внимание", "Состояние с данным номером уже существует");
        return false;
    }
    if (!this->has_choosen_representation)
    {
        QMessageBox box(QMessageBox::Question, "Внимание",
                        "Вы не выбрали графическое представление состояния. Использовать прозрачную заливку?",
                        QMessageBox::Yes | QMessageBox::No);
        auto result = box.exec();
        return result == QMessageBox::Yes;
    }
    return true;

}
void AddStatementFormController::closeWithAcceptingData()
{
    this->name = this->form.ui->NameLineEdit->text();
    this->number = this->form.ui->NumberLineEdit->text().toInt();
    if (!this->has_choosen_representation)
    {
        this->has_choosen_representation = true;
        this->is_given_by_color = true;
        QRgba64 col;
        col.setAlpha(0);
        col.setRed(0);
        col.setGreen(0);
        col.setBlue(0);
        this->color.setRgba64(col);

    }
    this->dialog_result = true;
    this->form.close();
}
bool AddStatementFormController::isOK()
{
    return this->dialog_result;
}

QString AddStatementFormController::getName()
{
    return this->name;
}
int AddStatementFormController::getNumber()
{
    return this->number;
}
bool AddStatementFormController::isGivenByColor()
{
    return this->is_given_by_color;
}
QPixmap AddStatementFormController::getSprite()
{
    return this->image;
}
QColor AddStatementFormController::getColor()
{
    return this->color;
}
