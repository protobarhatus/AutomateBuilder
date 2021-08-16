#include "addvariableform.h"
#include "ui_addvariableform.h"
#include "addvariableformcontroller.h"
#include "QGridLayout"
AddVariableForm::AddVariableForm(AddVariableFormController * icontroller,
                                 QString name, VariableType type, VariableClass v_class, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVariableForm)
{

    ui->setupUi(this);
    this->setGuiToGrid();
    this->controller = icontroller;
    this->ui->NameEdit->setText(name);
    if (type == LOGIC)
    {
        this->ui->isLogicRadioButton->setChecked(true);
    }
    else
    {
        this->ui->isValueRadioButton->setChecked(true);
    }
    if (v_class == GLOBAL)
    {
        this->ui->isGlobalRadioButton->setChecked(true);
    }
    else
    {
        this->ui->isIterativeRadioButton->setChecked(true);
    }
}

AddVariableForm::~AddVariableForm()
{
    delete ui;
}
void AddVariableForm::setLogicValue(bool value)
{
   this->ui->ValueLineEdit->setText(value ? "true" : "false");
}
void AddVariableForm::setValue(int value)
{
    QString value_in_string;
    value_in_string.setNum(value, 10);
    this->ui->ValueLineEdit->setText(value_in_string);
}
void AddVariableForm::on_isLogicRadioButton_clicked()
{
    if (this->ui->isLogicRadioButton->isChecked())
        this->setLogicType();
}
void AddVariableForm::setLogicType()
{

}
void AddVariableForm::setValueType()
{

}

void AddVariableForm::on_isValueRadioButton_clicked()
{
    if (this->ui->isValueRadioButton->isChecked())
        this->setValueType();
}



void AddVariableForm::on_OkCancelDialogBox_accepted()
{
    if (this->controller->checkDataBeforeAccepting())
    {
        this->controller->closeWithAcceptingData();
    }
}

void AddVariableForm::on_OkCancelDialogBox_rejected()
{
    this->close();
}
void AddVariableForm::setGuiToGrid()
{
    QGridLayout * layout = new QGridLayout (this);

    layout->addWidget(this->ui->NameLabel, 0, 0);
    layout->addWidget(this->ui->NameEdit, 0, 1);
    layout->addWidget(this->ui->TypeLabel, 1, 0);
    layout->addWidget(this->ui->VariablesTypeGroupBox, 2, 0, 2, 4);
    layout->addWidget(this->ui->ValueLabel, 4, 0);
    layout->addWidget(this->ui->ValueLineEdit, 5, 0, 1, 5);
    layout->addWidget(this->ui->ClassLabel, 6, 0);
    layout->addWidget(this->ui->VariableClassGroupBox, 7, 0, 2, 5);
    layout->addWidget(this->ui->OkCancelDialogBox, 9, 3, 1, 2);
}

