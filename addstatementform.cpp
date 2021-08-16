#include "addstatementform.h"
#include "ui_addstatementform.h"
#include "addstatementformcontroller.h"
#include <QGridLayout>
AddStatementForm::AddStatementForm(AddStatementFormController * icontroller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStatementForm)
{
    ui->setupUi(this);
    this->controller = icontroller;
    this->ui->ImageLabel->setText("");
    this->setGuiToGrid();
}

AddStatementForm::~AddStatementForm()
{
    delete ui;
}

void AddStatementForm::on_LoadImageButton_clicked()
{
    this->controller->loadImageButtonPressed();
}

void AddStatementForm::on_ChooseAColorButton_clicked()
{
    this->controller->changeColorButtonPressed();
}

void AddStatementForm::on_OkCancelDialogBox_accepted()
{
    if (this->controller->checkDataBeforeAccepting())
    {
        this->controller->closeWithAcceptingData();
    }
}

void AddStatementForm::on_OkCancelDialogBox_rejected()
{
    this->close();
}
void AddStatementForm::setGuiToGrid()
{
    QGridLayout * layout = new QGridLayout(this);

    layout->addWidget(this->ui->NameLabel, 0, 0);
    layout->addWidget(this->ui->NameLineEdit, 0, 1);

    layout->addWidget(this->ui->NumberLabel, 1, 0);
    layout->addWidget(this->ui->NumberLineEdit, 1, 1);

    layout->addWidget(this->ui->RepresentationLabel, 2, 0);
    layout->addWidget(this->ui->ImageLabel, 2, 1, 3, 1);
    layout->addWidget(this->ui->LoadImageButton, 2, 2);
    layout->addWidget(this->ui->OrLabel, 3, 2);
    layout->addWidget(this->ui->ChooseAColorButton, 4, 2);

    layout->addWidget(this->ui->OkCancelDialogBox, 6, 2, 1, 2);
}
