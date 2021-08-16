#include "createautomateform.h"
#include "ui_createautomateform.h"
#include "QGridLayout"
#include "controller.h"
#include "algorithm.h"
#include "map"
#include "QDesktopServices"
#include "aboutprogrammform.h"
CreateAutomateForm::CreateAutomateForm(Controller * icontroller, Algorithm * ialgorithm, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateAutomateForm)
{
    ui->setupUi(this);
    this->controller = icontroller;
    this->setGuiToGrid();
    this->algorithm = ialgorithm;
    this->update();
}

CreateAutomateForm::~CreateAutomateForm()
{
    delete ui;
}

void CreateAutomateForm::setGuiToGrid()
{
    QWidget *widget = new QWidget;
    this->setCentralWidget(widget);
    QGridLayout *layout = new QGridLayout(widget);

    layout->setColumnStretch(0, 2);
    layout->setColumnStretch(1, 3);
    layout->setColumnStretch(2, 5);
    layout->setColumnStretch(3, 6);

    layout->addWidget(this->ui->statement_label, 0, 0);
    layout->addWidget(this->ui->statements_list, 1, 0);
    layout->addWidget(this->ui->add_statement_button, 2, 0);
    layout->addWidget(this->ui->change_statement_button, 3, 0);
    layout->addWidget(this->ui->delete_statement_button, 4, 0);

    layout->addWidget(this->ui->environs_functions_label, 0, 1);
    layout->addWidget(this->ui->environs_functions_list, 1, 1);
    layout->addWidget(this->ui->add_environs_function_buton, 2, 1);
    layout->addWidget(this->ui->change_environs_function_button, 3, 1);
    layout->addWidget(this->ui->delete_environs_function_button, 4, 1);

    layout->addWidget(this->ui->variables_label, 0, 2);
    layout->addWidget(this->ui->variables_list, 1, 2);
    layout->addWidget(this->ui->add_variable_button, 2, 2);
    layout->addWidget(this->ui->change_variable_button, 3, 2);
    layout->addWidget(this->ui->delete_variable_button, 4, 2);

    layout->addWidget(this->ui->rules_label, 0, 3);
    layout->addWidget(this->ui->rules_list, 1, 3);
    layout->addWidget(this->ui->add_rule_button, 2, 3);
    layout->addWidget(this->ui->change_rule_button, 3, 3);
    layout->addWidget(this->ui->delete_rule_button, 4, 3);

    layout->addWidget(this->ui->ReadyButton, 0, 4);
}

void CreateAutomateForm::on_add_variable_button_clicked()
{
    this->controller->addVariableButtonPressed();
}
void CreateAutomateForm::update()
{
    this->displayVariables();
    this->displayStatements();
    this->displayRules();
    this->displayEnvironsFunction();
}
void CreateAutomateForm::displayVariables()
{
    this->ui->variables_list->clear();

    const std::map<QString, std::shared_ptr<ValueVariable>> & global_variables = this->algorithm->getGlobalVariablesList();
    for (auto &it : global_variables)
    {
        QListWidgetItem * item = new QListWidgetItem("global int " + it.first + " = " + it.second->getStringFormula());
        item->setWhatsThis(it.first);
        this->ui->variables_list->addItem(item);
    }

    const std::map<QString, std::shared_ptr<ValueVariable>> & value_variables = this->algorithm->getValueVariablesList();
    for (auto &it : value_variables)
    {

        QListWidgetItem * item = new QListWidgetItem("local int " + it.first + " = " + it.second->getStringFormula());
        item->setWhatsThis(it.first);
        this->ui->variables_list->addItem(item);
    }
    const std::map<QString, std::shared_ptr<LogicVariable>> & global_logic_variables = this->algorithm->getGlobalLogicVariablesList();
    for (auto &it : global_logic_variables)
    {
        QListWidgetItem * item = new QListWidgetItem("global bool " + it.first + " = " + it.second->getStringFormula());
        item->setWhatsThis(it.first);
        this->ui->variables_list->addItem(item);
    }
    const std::map<QString, std::shared_ptr<LogicVariable>> & logic_variables = this->algorithm->getLogicVariablesList();
    for (auto &it : logic_variables)
    {
        QListWidgetItem * item = new QListWidgetItem("local bool " + it.first + " = " + it.second->getStringFormula());
        item->setWhatsThis(it.first);
        this->ui->variables_list->addItem(item);
    }
}
void CreateAutomateForm::displayStatements()
{
    this->ui->statements_list->clear();
    const std::map<int, Statement*> & statements = this->algorithm->getStatementsList();
    for (auto &it : statements)
    {
        QString number_in_string;
        number_in_string.setNum(it.first);
        QListWidgetItem * item = new QListWidgetItem(number_in_string + " - " + it.second->getName());
        //16 x 16 - размер иконки в list-е
        it.second->getReadyToDrawing(16, 16);
        item->setIcon(QIcon(it.second->getGraphicalRepresentation()));
        item->setWhatsThis(number_in_string);
        this->ui->statements_list->addItem(item);
    }
}
void CreateAutomateForm::displayRules()
{
    this->ui->rules_list->clear();
    const std::map<int, std::shared_ptr<Rule>> & rules = this->algorithm->getRulesList();
    for (auto &it : rules)
    {
        QListWidgetItem * item = new QListWidgetItem((it.second->isGlobal() ? "(global) " : "(local) ") +
                                                                             it.second->getStringRepresentation());
        QString number_in_string;
        number_in_string.setNum(it.first);
        item->setWhatsThis(number_in_string);
        this->ui->rules_list->addItem(item);
    }
}
void CreateAutomateForm::displayEnvironsFunction()
{
    this->ui->environs_functions_list->clear();
    const std::map<QString, std::shared_ptr<FunctionCell>> & functions = this->algorithm->getEnvironsFunctionsList();
    for (auto &it : functions)
    {
        QListWidgetItem * item = new QListWidgetItem((it.second->isAllowed() ? "(ALLOWED) " : "(BANNED) ") +
                                                     it.second->getName() + " " + it.second->getDefinition());
        item->setWhatsThis(it.first);
        this->ui->environs_functions_list->addItem(item);
    }
}
void CreateAutomateForm::on_change_variable_button_clicked()
{

    if (this->ui->variables_list->currentRow() == -1)
    {
        return;
    }
    //в поле whatsThis хранится имя переменной без указания типа и значения
    this->controller->changeVariableButtonPressed(this->ui->variables_list->currentItem()->whatsThis());
}

void CreateAutomateForm::on_delete_variable_button_clicked()
{
    if (this->ui->variables_list->currentRow() == -1)
    {
        return;
    }
    //в поле whatsThis хранится номер состояния.
    this->controller->deleteVariableButtonPressed(this->ui->variables_list->currentItem()->whatsThis());
}

void CreateAutomateForm::on_add_statement_button_clicked()
{
    this->controller->addStatementButtonPressed();
}

void CreateAutomateForm::on_change_statement_button_clicked()
{
    if (this->ui->statements_list->currentRow() == -1)
    {
        return;
    }
    this->controller->changeStatementButtonPressed(this->ui->statements_list->currentItem()->whatsThis().toInt());
}

void CreateAutomateForm::on_delete_statement_button_clicked()
{
    if (this->ui->statements_list->currentRow() == -1)
    {
        return;
    }
    this->controller->deleteStatementButtonPressed(this->ui->statements_list->currentItem()->whatsThis().toInt());
}

void CreateAutomateForm::on_add_rule_button_clicked()
{

    this->controller->addRuleButtonPressed();
}

void CreateAutomateForm::on_change_rule_button_clicked()
{
    if (this->ui->rules_list->currentRow() == -1)
    {
        return;
    }
    this->controller->changeRuleButtonPressed(this->ui->rules_list->currentItem()->whatsThis().toInt());
}

void CreateAutomateForm::on_delete_rule_button_clicked()
{
    if (this->ui->rules_list->currentRow() == -1)
    {
        return;
    }
    this->controller->deleteRuleButtonPressed(this->ui->rules_list->currentItem()->whatsThis().toInt());
}

void CreateAutomateForm::on_add_environs_function_buton_clicked()
{
    this->controller->addEnvironsFunctionButtonPressed();
}
void CreateAutomateForm::setAlgorithm(Algorithm * alg)
{
    this->algorithm = alg;
}
void CreateAutomateForm::on_change_environs_function_button_clicked()
{
    if (this->ui->environs_functions_list->currentRow() == -1)
    {
        return;
    }
    this->controller->changeEnvironsFunctionButtonPressed(this->ui->environs_functions_list->currentItem()->whatsThis());
}

void CreateAutomateForm::on_delete_environs_function_button_clicked()
{
    if (this->ui->environs_functions_list->currentRow() == -1)
    {
        return;
    }
    this->controller->deleteEnvironsFunctionButtonPressed(this->ui->environs_functions_list->currentItem()->whatsThis());
}

void CreateAutomateForm::on_ReadyButton_clicked()
{
    if (!this->algorithm->isValid())
    {
        QMessageBox::information(this, "Внимание", "Некоторые формулы недействительны.");
        return;
    }
    this->controller->openSimulator();
}

void CreateAutomateForm::on_saveAction_triggered()
{
    this->controller->saveAutomate();
}

void CreateAutomateForm::on_openAction_triggered()
{
    this->controller->loadAutomateButtonPressed();
}

void CreateAutomateForm::on_saveAsAction_triggered()
{
    this->controller->saveAsAutomateButtonPressed(this);
}

void CreateAutomateForm::on_Help_triggered()
{
    if (!QDesktopServices::openUrl(QUrl("file:Automate builder's help.chm")))
    {
        if (!QDesktopServices::openUrl(QUrl("file:Automate builder's help.pdf")))
        {
            QMessageBox::critical(this, "Невозможно открыть справку", "В корневой директории отсутствуют файлы справки");
        }
    }
}

void CreateAutomateForm::on_aboutProgrammAction_triggered()
{
    AboutProgrammForm form;
    form.exec();
}
