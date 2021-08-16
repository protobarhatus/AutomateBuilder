#include "simulationpropetriesform.h"
#include "ui_simulationpropetriesform.h"
#include "somedataworks.h"
#include "simulationpropetries.h"
#include "QGridLayout"
SimulationPropetriesForm::SimulationPropetriesForm(SimulationPropetries & ipropetries, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationPropetriesForm), propetries(ipropetries)
{
    ui->setupUi(this);
    QString string_in_number;
    string_in_number.setNum(this->propetries.getTimeBetweenIterations());
    this->ui->timeLineEdit->setText(string_in_number);
    if (this->propetries.getStopParam() != SimulationPropetries::STOP_DONT)
    {
        this->ui->stopSimulationCheckBox->setChecked(true);
        string_in_number.setNum(propetries.getStep());
        if (this->propetries.getStopParam() == SimulationPropetries::STOP_ON_STEP)
        {
            this->ui->onStepRadioButton->setChecked(true);
            this->ui->onStepLineEdit->setText(string_in_number);
        }
        if (this->propetries.getStopParam() == SimulationPropetries::STOP_EVERY_STEPS)
        {
            this->ui->everyStepRadioButton->setChecked(true);
            this->ui->everyStepLineEdit->setText(string_in_number);
        }
    }
    this->setGuiToGrid();
}

SimulationPropetriesForm::~SimulationPropetriesForm()
{
    delete ui;
}
void SimulationPropetriesForm::setGuiToGrid()
{
    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(this->ui->timeLabel, 0, 0, 1, 3);
    layout->addWidget(this->ui->timeLineEdit, 0, 3);
    layout->addWidget(this->ui->stopSimulationCheckBox, 1, 0, 1, 3);
    layout->addWidget(this->ui->onStepRadioButton, 2, 1);
    layout->addWidget(this->ui->onStepLineEdit, 2, 2);
    layout->addWidget(this->ui->everyStepRadioButton, 3, 1);
    layout->addWidget(this->ui->everyStepLineEdit, 3, 2);
    layout->addWidget(this->ui->okCancelButtonBox, 4, 2, 1, 2);
}


void SimulationPropetriesForm::on_stopSimulationCheckBox_stateChanged(int state)
{
    bool is_checked = state == Qt::Checked;

    this->ui->onStepRadioButton->setEnabled(is_checked);
    this->ui->everyStepRadioButton->setEnabled(is_checked);
    this->ui->onStepLineEdit->setEnabled(this->ui->onStepRadioButton->isChecked() && this->ui->onStepRadioButton->isEnabled());
    this->ui->everyStepLineEdit->setEnabled(this->ui->everyStepRadioButton->isChecked() && this->ui->everyStepRadioButton->isEnabled());
}

void SimulationPropetriesForm::on_onStepRadioButton_toggled(bool checked)
{
    this->ui->onStepLineEdit->setEnabled(checked);
}

void SimulationPropetriesForm::on_everyStepRadioButton_toggled(bool checked)
{
    this->ui->everyStepLineEdit->setEnabled(checked);
}
bool SimulationPropetriesForm::checkDataBeforeAccepting()
{
    if (!checkLineEditForDataPresense(this->ui->timeLineEdit, "время между итерациями", this))
        return false;
    if (!checkForNumber(this->ui->timeLineEdit, "время между итерациями", this))
        return false;
    if (!checkForOverflow(this->ui->timeLineEdit, "время между итерациями", this))
        return false;
    if (this->ui->stopSimulationCheckBox->isChecked())
    {
        if (this->ui->onStepRadioButton->isChecked())
        {
            if (!checkLineEditForDataPresense(this->ui->onStepLineEdit, "шаг, на котором симуляция должна остановиться", this))
                return false;
            if (!checkForNumber(this->ui->onStepLineEdit, "шаг, на котором симуляция должна остановиться", this))
                return false;
            if (!checkForOverflow(this->ui->onStepLineEdit, "шаг, на котором симуляция должна остановиться", this))
                return false;
        }
        if (this->ui->everyStepRadioButton->isChecked())
        {
            if (!checkLineEditForDataPresense(this->ui->everyStepLineEdit, "количество шагов между остановками", this))
                return false;
            if (!checkForNumber(this->ui->everyStepLineEdit, "количество шагов между остановками", this))
                return false;
            if (!checkForOverflow(this->ui->onStepLineEdit, "количество шагов между остановками", this))
                return false;
        }
    }
    return true;
}
void SimulationPropetriesForm::closeWithAcceptingData()
{
    this->propetries.setTimeBetweenIterations(this->ui->timeLineEdit->text().toInt());
    if (!this->ui->stopSimulationCheckBox->isChecked())
        this->propetries.dontStop();
    else
    {
        if (this->ui->onStepRadioButton->isChecked())
        {
            this->propetries.stopOnStep(this->ui->onStepLineEdit->text().toInt());
        }
        if (this->ui->everyStepRadioButton->isChecked())
        {
            this->propetries.stopEveryStep(this->ui->everyStepLineEdit->text().toInt());
        }
    }
    this->is_ok = true;
    this->close();
}
bool SimulationPropetriesForm::isOk()
{
    return this->is_ok;
}

void SimulationPropetriesForm::on_okCancelButtonBox_accepted()
{
    if (this->checkDataBeforeAccepting())
    {
        this->closeWithAcceptingData();
    }
}

void SimulationPropetriesForm::on_okCancelButtonBox_rejected()
{
    this->close();
}
