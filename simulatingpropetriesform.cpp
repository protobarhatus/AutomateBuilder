#include "simulatingpropetriesform.h"
#include "ui_simulatingpropetriesform.h"
#include "simulatingpropetries.h"
#include "QGridLayout"
#include "algorithm.h"
#include "somedataworks.h"
SimulatingPropetriesForm::SimulatingPropetriesForm(Algorithm * alg, SimulatingPropetries & ipropetries, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulatingPropetriesForm), propetries(ipropetries), algorithm(alg)
{
    ui->setupUi(this);

    this->setGuiToTheGrid();
    this->displayAllData();
}

SimulatingPropetriesForm::~SimulatingPropetriesForm()
{
    delete ui;
}
void SimulatingPropetriesForm::setGuiToTheGrid()
{
    QGridLayout * layout = new QGridLayout(this);
    layout->setColumnStretch(2, 5);

    layout->addWidget(this->ui->widthLabel, 0, 0);
    layout->addWidget(this->ui->widthLineEdit, 0, 1);
    layout->addWidget(this->ui->heightLabel, 0, 2);
    layout->addWidget(this->ui->heightLineEdit, 0, 3);

    layout->addWidget(this->ui->cellsWidthLabel, 1, 0);
    layout->addWidget(this->ui->cellsWidthLineEdit, 1, 1);
    layout->addWidget(this->ui->cellsHeightLabel, 1, 2);
    layout->addWidget(this->ui->cellsHeightLineEdit, 1, 3);

    layout->addWidget(this->ui->statementsList, 2, 0, 1, 4);
    layout->addWidget(this->ui->OkCancelButtonBox, 3, 2, 1, 2);

}
void SimulatingPropetriesForm::visualizeStatementsList()
{
    const std::map<int, Statement*> & statements =
            this->algorithm->getStatementsList();
    this->ui->statementsList->clear();
    for (auto &it : statements)
    {
        QString number_in_string;
        number_in_string.setNum(it.first);

        QListWidgetItem * item = new QListWidgetItem(QIcon(std::move(it.second->getSprite(16 , 16))), number_in_string + " - "
                                                     + it.second->getName());

        item->setWhatsThis(number_in_string);
        this->ui->statementsList->addItem(item);
    }
}
void SimulatingPropetriesForm::displayAllData()
{
    this->visualizeStatementsList();
    this->ui->widthLineEdit->setText(QString::number(this->propetries.getWidth()));
    this->ui->heightLineEdit->setText(QString::number(this->propetries.getHeight()));
    this->ui->cellsWidthLineEdit->setText(QString::number(this->propetries.getCellsWidth()));
    this->ui->cellsHeightLineEdit->setText(QString::number(this->propetries.getCellsHeight()));
}
bool SimulatingPropetriesForm::checkDataBeforeAccepting()
{
    if (!checkLineEditForDataPresense(this->ui->widthLineEdit, "ширину поля", this))
        return false;
    if (!checkLineEditForDataPresense(this->ui->heightLineEdit, "высоту поля", this))
        return false;
    if (!checkLineEditForDataPresense(this->ui->cellsWidthLineEdit, "ширину клетки", this))
        return false;
    if (!checkLineEditForDataPresense(this->ui->cellsHeightLineEdit, "высоту клетки", this))
        return false;
    if (!checkForNumber(this->ui->widthLineEdit, "Ширина поля", this))
        return false;
    if (!checkForNumber(this->ui->heightLineEdit, "Высота поля", this))
        return false;
    if (!checkForNumber(this->ui->cellsWidthLineEdit, "Ширина клетки", this))
        return false;
    if (!checkForNumber(this->ui->cellsHeightLineEdit, "Высота клетки", this))
        return false;
    if (this->ui->statementsList->currentRow() == -1)
    {
        QMessageBox::information(this, "Внимание", "Выберите нулевое состояние.");
        return false;
    }
    if (!checkForOverflow(this->ui->widthLineEdit, "Ширина поля", this))
        return false;
    if (!checkForOverflow(this->ui->heightLineEdit, "Высота поля", this))
        return false;
    if (!checkForOverflow(this->ui->cellsWidthLineEdit, "Ширина клетки", this))
        return false;
    if (!checkForOverflow(this->ui->cellsHeightLineEdit, "Высота клетки", this))
        return false;
    return true;
}
void SimulatingPropetriesForm::closeWithAcceptingData()
{
    try {
        this->propetries.setWidth(this->ui->widthLineEdit->text().toInt());
        this->propetries.setHeight(this->ui->heightLineEdit->text().toInt());
        this->propetries.setCellsWidth(this->ui->cellsWidthLineEdit->text().toInt());
        this->propetries.setCellsHeight(this->ui->cellsHeightLineEdit->text().toInt());
        this->propetries.default_statements = this->algorithm->getStatement(this->ui->statementsList->currentItem()->whatsThis().toInt());
        this->is_ok = true;
        this->close();
    } catch (QString exception) {
        QMessageBox::information(this, "Внимание", exception);
    }
}

bool SimulatingPropetriesForm::isOk()
{
    return this->is_ok;
}






void SimulatingPropetriesForm::on_OkCancelButtonBox_accepted()
{
    if (this->checkDataBeforeAccepting())
    {
        this->closeWithAcceptingData();
    }
}

void SimulatingPropetriesForm::on_OkCancelButtonBox_rejected()
{
    this->close();
}
