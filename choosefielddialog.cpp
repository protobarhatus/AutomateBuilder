#include "choosefielddialog.h"
#include "ui_choosefielddialog.h"
#include "fielddistributor.h"
#include <QMessageBox>
#include "configuration.h"
ChooseFieldDialog::ChooseFieldDialog(FieldDistributor * idistributor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseFieldDialog)
{
    ui->setupUi(this);
    this->distributor = idistributor;
    this->update();
    this->setGuiToGrid();
}
void ChooseFieldDialog::setGuiToGrid()
{
    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(this->ui->configurationLabel, 0, 0, 1, 2);
    layout->addWidget(this->ui->configurationList, 1, 0, 10, 2);
    layout->addWidget(this->ui->configurationLineEdit, 1, 2);
    layout->addWidget(this->ui->addButton, 2, 2);
    layout->addWidget(this->ui->renameButton, 3, 2);
    layout->addWidget(this->ui->deleteButton, 4, 2);
    layout->addWidget(this->ui->okCancelDialogBox, 10, 2, 1, 2);
}
ChooseFieldDialog::~ChooseFieldDialog()
{
    delete ui;
}
void ChooseFieldDialog::update()
{
    this->fillFieldsList();
}
void ChooseFieldDialog::fillFieldsList()
{
    this->ui->configurationList->clear();
    const std::map<QString, std::unique_ptr<Configuration>> & fields = this->distributor->getFieldsList();
    for (auto &it : fields)
    {
        QListWidgetItem * item = new QListWidgetItem(it.first);
        item->setWhatsThis(it.first);
        this->ui->configurationList->addItem(item);
    }
}
void ChooseFieldDialog::on_addButton_clicked()
{
    if (this->ui->configurationLineEdit->text().isEmpty())
        return;
    this->distributor->addField(this->ui->configurationLineEdit->text());
    this->ui->configurationList->setCurrentRow(-1);
    this->ui->configurationLineEdit->setText("");
    this->update();
}

void ChooseFieldDialog::on_renameButton_clicked()
{
    if (this->ui->configurationList->currentRow() == -1)
        return;
    this->distributor->renameField(this->ui->configurationList->currentItem()->whatsThis(),
                                   this->ui->configurationLineEdit->text());
    this->update();
}

void ChooseFieldDialog::on_deleteButton_clicked()
{
    if (this->ui->configurationList->currentRow() == -1)
        return;
    auto answer = QMessageBox::warning(this, "Внимание", "Вы действительно хотите удалить конфигурацию? Отменить это действие\
будет невозможно", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (answer == QMessageBox::No)
        return;
    this->distributor->eraseField(this->ui->configurationList->currentItem()->whatsThis());
    this->update();
}

void ChooseFieldDialog::on_okCancelDialogBox_accepted()
{
    if (this->ui->configurationList->currentRow() == -1)
    {
        QMessageBox::critical(this, "Ошибка", "Выберите текущую конфигурацию");
        return;
    }
    this->distributor->selectField(this->ui->configurationList->currentItem()->whatsThis());
    this->is_ok = true;
    this->close();
}

void ChooseFieldDialog::on_okCancelDialogBox_rejected()
{
    this->close();
}
bool ChooseFieldDialog::isOk()
{
    return this->is_ok;
}

void ChooseFieldDialog::on_configurationList_itemClicked(QListWidgetItem *item)
{
    this->ui->configurationLineEdit->setText(item->whatsThis());
}
