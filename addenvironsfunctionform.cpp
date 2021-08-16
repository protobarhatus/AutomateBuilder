#include "addenvironsfunctionform.h"
#include "ui_addenvironsfunctionform.h"
#include "QGridLayout"
#include "addenvironsfunctionformcontroller.h"
AddEnvironsFunctionForm::AddEnvironsFunctionForm(AddEnvironsFunctionFormController * icontroller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEnvironsFunctionForm)
{
    ui->setupUi(this);
    this->controller = icontroller;
    this->setGuiToTheGrid();
}

AddEnvironsFunctionForm::~AddEnvironsFunctionForm()
{
    delete ui;
}
void AddEnvironsFunctionForm::setGuiToTheGrid()
{
    QGridLayout * layout = new QGridLayout(this);

    layout->addWidget(this->ui->NameLabel, 0, 0);
    layout->addWidget(this->ui->NameLineEdit, 0, 1, 1, 3);
    layout->addWidget(this->ui->XLabel, 1, 0);
    layout->addWidget(this->ui->XLineEdit, 1, 1);
    layout->addWidget(this->ui->YLabel, 1, 2);
    layout->addWidget(this->ui->YLineEdit, 1, 3);
    layout->addWidget(this->ui->isAllowedCheckBox, 2, 0, 1, 4);
    layout->addWidget(this->ui->OkCancelButtonBox, 3, 1, 1, 3);
}

void AddEnvironsFunctionForm::on_OkCancelButtonBox_accepted()
{
    if (this->controller->checkDataBeforeAccepting())
    {
        this->controller->closeWithAcceptingData();
    }
}

void AddEnvironsFunctionForm::on_OkCancelButtonBox_rejected()
{
    this->close();
}
