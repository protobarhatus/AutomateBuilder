#include "addruleform.h"
#include "ui_addruleform.h"
#include <QGridLayout>
#include "addruleformcontroller.h"
AddRuleForm::AddRuleForm(AddRuleFormController * icontroller, QString icondition, QString iaction,
                         QString second_action, bool iis_global, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRuleForm)
{
    ui->setupUi(this);

    this->ui->ConditionLineEdit->setText(icondition);
    this->ui->ActionLineEdit->setText(iaction);
    this->ui->elseLineEdit->setText(second_action);
    this->ui->isGlobalRadioButton->setChecked(iis_global);
    this->controller = icontroller;
    this->setGuiToGrid();
    //QObject::connect(this->ui->OkCancelButtonBox, SIGNAL(this->ui->OkCancelButtonBox->accepted()), this, SLOT(this->on_OkCancelButtonBox_accepted()));
}

AddRuleForm::~AddRuleForm()
{
    delete ui;
}
void AddRuleForm::setGuiToGrid()
{
    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(this->ui->ConditionLabel, 0, 0);
    layout->addWidget(this->ui->ConditionLineEdit, 0, 1, 1, 3);
    layout->addWidget(this->ui->ActionLabel, 1, 0);
    layout->addWidget(this->ui->ActionLineEdit, 1, 1, 1, 3);
    layout->addWidget(this->ui->elseLabel, 2, 0);
    layout->addWidget(this->ui->elseLineEdit, 2, 1, 1, 3);

    layout->addWidget(this->ui->isGlobalRadioButton, 3, 0, 1, 2);
    layout->addWidget(this->ui->isLocalRadioButton, 4, 0, 1, 2);
    layout->addWidget(this->ui->OkCancelButtonBox, 5, 2, 1, 2);
}
void AddRuleForm::on_OkCancelButtonBox_accepted()
{
    if (this->controller->checkDataBeforeAccepting())
    {
        this->controller->closeWithAcceptingData();
    }
}
void AddRuleForm::on_OkCancelButtonBox_rejected()
{
    this->close();
}
