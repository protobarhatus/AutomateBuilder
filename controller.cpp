#include "controller.h"
#include "automate.h"
#include "startwindow.h"
#include "createautomateform.h"
#include "algorithm.h"
#include "addvariableformcontroller.h"
#include "addstatementformcontroller.h"
#include "addruleformcontroller.h"
#include "addenvironsfunctionformcontroller.h"
#include "simulatingform.h"
#include "statementscounter.h"
#include "simulatingpropetries.h"
#include "simulatingpropetriesform.h"
#include "simulationpropetries.h"
#include "simulationpropetriesform.h"
#include "fileparser.h"
#include "field.h"
#include "fielddistributor.h"
#include "choosefielddialog.h"
#include <QDir>
Controller::Controller()
{

}
bool Controller::createAutomateButtonPressed(QWidget * parent)
{
    QString path;
    path = QFileDialog::getSaveFileName(parent, QString("Save the automate"), QApplication::applicationDirPath() + "\\Automates",
                                 "Automates(*.automate)");
    if (path.length() == 0)
        return false;
    this->current_path = path;
    if (this->automate)
        delete this->automate;
    this->automate = new Automate;
    this->automate->createAutomateFile(path);
    if (this->start_window)
    {
        this->start_window->close();
        delete start_window;
        start_window = nullptr;
    }

    SingleCounter::getCounter().setStatementsList(this->automate->getAlgorithm()->getStatementsList());
    if (this->create_automate_window)
        delete this->create_automate_window;
    this->create_automate_window = new CreateAutomateForm(this, this->automate->getAlgorithm());
    QFileInfo file_name(path);
    this->create_automate_window->setWindowTitle(file_name.fileName());
    this->create_automate_window->show();
    return true;
}
void Controller::saveAutomate()
{

    this->saveAutomate(this->current_path);

}
void Controller::saveAutomate(QString path)
{
    QWidget widget;
    widget.setWindowTitle(QString("Сохранение..."));
    widget.setGeometry(400, 400, 300, 100);
    widget.show();
    this->automate->saveAutomate(path);
    widget.close();
}
bool Controller::saveAsAutomateButtonPressed(QWidget * parent)
{
    QString path;
    path = QFileDialog::getSaveFileName(parent, QString("Save the automate"), QApplication::applicationDirPath() + "\\Automates",
                                 "Automates(*.automate)");
    if (path.length() == 0)
        return false;
    this->current_path = path;
    this->saveAutomate(path);
    QFileInfo file_name(path);
    this->create_automate_window->setWindowTitle(file_name.fileName());
}
void Controller::loadAutomateButtonPressed(QWidget * parent)
{
    QString path;
    path = QFileDialog::getOpenFileName(parent, QString("Open the automate"), QApplication::applicationDirPath() + "\\Automates",
                                        "Automates(*.automate)");
    if (path.isEmpty())
        return;
    if (!loadAutomate(path))
        return;
    if (this->start_window)
    {
        this->start_window->close();
        delete start_window;
        this->start_window = nullptr;
    }
    //SingleCounter::getCounter().setStatementsList(this->automate->getAlgorithm()->getStatementsList());
    if (!this->create_automate_window)
        this->create_automate_window = new CreateAutomateForm(this, this->automate->getAlgorithm());
    else
        this->create_automate_window->setAlgorithm(this->automate->getAlgorithm());
    QFileInfo file_name(path);
    this->create_automate_window->setWindowTitle(file_name.fileName());
    this->create_automate_window->show();
    this->create_automate_window->update();
}
bool Controller::loadAutomate(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QString automate = file.readAll();

    Automate * new_automate = new Automate(true);
    FileParser parser(new_automate->getAlgorithm(), new_automate->getField());
    try {
        parser.readAutomate(automate);
    } catch (QString exception) {
        QMessageBox::critical(nullptr, "Ошибка при загрузке файла", "Файл неккоректен. " + exception);
        delete new_automate;
        return false;
    }
    if (this->automate)
        delete this->automate;
    this->automate = new_automate;
    this->current_path = path;
    file.close();
    return true;
}
void Controller::start()
{
    this->start_window = new StartWindow(this);
    this->start_window->show();
}
bool Controller::isVariablesNameFree(QString name, VariableClass v_class)
{


        return !this->automate->getAlgorithm()->hasIterativeVariable(name) &&
    !this->automate->getAlgorithm()->hasGlobalVariable(name);

}
void Controller::addVariableButtonPressed()
{
    AddVariableFormController controller(this, this->getAutomate());
    controller.start("", "", LOGIC, ITERATIVE);
    bool is_global = controller.getClass() == GLOBAL;
    if (controller.getType() == LOGIC)
    {
        this->automate->getAlgorithm()->addLogicVariable(controller.getName(), is_global, controller.getFormula(), controller.getLogicValue());
    }
    if (controller.getType() == VALUE)
    {
        this->automate->getAlgorithm()->addValueVariable(controller.getName(), is_global, controller.getFormula(), controller.getNumericValue());
    }
    this->create_automate_window->update();
}

Automate * Controller::getAutomate()
{
    return this->automate;
}
void Controller::changeLogicVariable(QString name)
{
    std::shared_ptr<LogicVariable> variable = this->automate->getAlgorithm()->getLogicVariable(name);
    bool were_global = variable->isGlobal();
    AddVariableFormController controller(this, this->getAutomate());
    controller.start(variable->getName(), variable->getStringFormula(), LOGIC, variable->isGlobal() ? GLOBAL : ITERATIVE);
    if (!controller.isOK())
        return;
    while (controller.getType() == VALUE)
    {
        QMessageBox::information(this->create_automate_window, "Внимание", "Нельзя сменить тип переменной.");
        controller.start(variable->getName(), variable->getStringFormula(), LOGIC, variable->isGlobal() ? GLOBAL : ITERATIVE);
    }
    this->automate->getAlgorithm()->changeLogicVariable(variable->getName(), controller.getName(),
                                                        were_global, controller.getClass() == GLOBAL);
    variable->setName(controller.getName());
    variable->setFormula(controller.getFormula(), controller.getLogicValue());
    variable->setGlobality(controller.getClass() == GLOBAL);
}
void Controller::changeValueVariable(QString name)
{
    std::shared_ptr<ValueVariable> variable = this->automate->getAlgorithm()->getValueVariable(name);
    bool were_global = variable->isGlobal();
    AddVariableFormController controller(this, this->getAutomate());
    controller.start(variable->getName(), variable->getStringFormula(), VALUE, variable->isGlobal() ? GLOBAL : ITERATIVE);
    if (!controller.isOK())
        return;
    while (controller.getType() == LOGIC)
    {
        QMessageBox::information(this->create_automate_window, "Внимание", "Нельзя сменить тип переменной.");
        controller.start(variable->getName(), variable->getStringFormula(), VALUE, variable->isGlobal() ? GLOBAL : ITERATIVE);
    }
    this->automate->getAlgorithm()->changeValueVariable(variable->getName(), controller.getName(),
                                                        were_global, controller.getClass() == GLOBAL);
    variable->setName(controller.getName());
    variable->setFormula(controller.getFormula(), controller.getNumericValue());
    variable->setGlobality(controller.getClass() == GLOBAL);

}

void Controller::changeVariableButtonPressed(QString name)
{
    if (this->automate->getAlgorithm()->hasLogicVariable(name))
    {
        this->changeLogicVariable(name);
    }
    if (this->automate->getAlgorithm()->hasValueVariable(name))
    {
        this->changeValueVariable(name);
    }
    this->automate->getAlgorithm()->reBuildAllStringFormulas();
    this->create_automate_window->update();
}
void Controller::deleteVariableButtonPressed(QString name)
{
    this->automate->getAlgorithm()->deleteVariable(name);
    this->automate->getAlgorithm()->reCompileAllFormulas(this->automate->getField());
    this->create_automate_window->update();
}
void Controller::addStatementButtonPressed()
{
    AddStatementFormController controller(this);
    controller.start();
    if (!controller.isOK())
        return;
    this->automate->getAlgorithm()->addStatement(controller.getName(), controller.getNumber(), controller.isGivenByColor(),
                                                 controller.getColor(), controller.getSprite());
    this->create_automate_window->update();
    SingleCounter::getCounter().addElement(controller.getNumber(), this->automate->getAlgorithm()->getStatement(
                                               controller.getNumber()));
}
void Controller::changeStatementButtonPressed(int number)
{
    Statement * statement = this->automate->getAlgorithm()->getStatement(number);
    AddStatementFormController controller(this, statement->getName(), statement->getNumber());
    if (statement->isGivenByColor())
    {
        controller.setColor(statement->getColor());
    }
    else
    {
        controller.setImage(statement->getSprite());
    }
    controller.start();
    if (!controller.isOK())
        return;
    this->automate->getAlgorithm()->changeStatement(statement->getName(), controller.getName(),
                                                    statement->getNumber(), controller.getNumber());
    statement->setName(controller.getName());
    statement->setNumber(controller.getNumber());
    if (controller.isGivenByColor())
    {
        statement->setColor(controller.getColor());
    }
    else
    {
        statement->setSprite(controller.getSprite());
    }
    this->automate->getAlgorithm()->reBuildAllStringFormulas();
    this->create_automate_window->update();
    SingleCounter::getCounter().updateStatementsNumber();
}
void Controller::deleteStatementButtonPressed(int number)
{
    this->automate->getAlgorithm()->deleteStatement(number);
    this->automate->getAlgorithm()->reCompileAllFormulas(this->automate->getField());
    this->create_automate_window->update();
    this->automate->getField()->uninitializeAllFields();
    SingleCounter::getCounter().deleteElement(number);
}
void Controller::addRuleButtonPressed()
{
    AddRuleFormController controller(this, "", "", "", false);
    controller.start();
    if (!controller.isOK())
        return;
    Rule rule;
    rule.setCondition(controller.getStrCondition(), controller.getCondition());
    rule.setAction(controller.getStrAction(), controller.getAction());
    rule.setSecondAction(controller.getStrSecondAction(), controller.getSecondAction());
    rule.setGlobality(controller.isGlobal());
    this->automate->getAlgorithm()->addRule(rule);
    this->create_automate_window->update();
}
void Controller::changeRuleButtonPressed(int number)
{
    std::shared_ptr<Rule> rule = this->automate->getAlgorithm()->getRule(number);
    AddRuleFormController controller(this, rule->getStringCondition(), rule->getStringAction(),
                                     rule->getStringSecondAction(), rule->isGlobal());
    controller.start();
    if (!controller.isOK())
        return;
    rule->setCondition(controller.getStrCondition(), controller.getCondition());
    rule->setAction(controller.getStrAction(), controller.getAction());
    rule->setGlobality(controller.isGlobal());
    this->create_automate_window->update();
}
void Controller::deleteRuleButtonPressed(int number)
{
    this->automate->getAlgorithm()->deleteRule(number);
    this->create_automate_window->update();
}
void Controller::addEnvironsFunctionButtonPressed()
{
    AddEnvironsFunctionFormController controller(this, "", 0, 0, true);
    controller.start();
    if (!controller.isOk())
        return;
    this->automate->getAlgorithm()->addEnvironsFunction(controller.getName(), controller.getX(),
                                                        controller.getY(), controller.isAllowed());
    this->create_automate_window->update();
}
void Controller::changeEnvironsFunctionButtonPressed(QString name)
{
    std::shared_ptr<FunctionCell> function = this->automate->getAlgorithm()->getEnvironsFunction(name);
    AddEnvironsFunctionFormController controller(this, function->getName(), function->getX(), function->getY(),
                                                 function->isAllowed());
    controller.start();
    if (!controller.isOk())
        return;
    function->setName(controller.getName());
    function->setX(controller.getX());
    function->setY(controller.getY());
    this->automate->getAlgorithm()->changeEnvironsFunction(name, function->getName());
    if (function->isAllowed() && !controller.isAllowed())
    {
        this->automate->getAlgorithm()->banEnvironsFunction(function->getName());
    }
    if (!function->isAllowed() && controller.isAllowed())
    {
        this->automate->getAlgorithm()->allowEnvironsFunction(function->getName());
    }
    function->setPermissibility(controller.isAllowed());
    this->automate->getAlgorithm()->reBuildAllStringFormulas();
    this->create_automate_window->update();
}
void Controller::deleteEnvironsFunctionButtonPressed(QString name)
{
    this->automate->getAlgorithm()->deleteEnvironsFunction(name);
    this->automate->getAlgorithm()->reCompileAllFormulas(this->automate->getField());
    this->create_automate_window->update();
}
void Controller::openSimulator()
{
    this->automate->getAlgorithm()->getReadyBeforeSimulating();

    if (!this->automate->getField()->hasSelection())
    {
        bool result = this->openFieldsDistributingDialog();
        if (!result)
            return;
    }
    else if (!this->automate->getField()->isFieldInitialized())
    {

        if (!this->callFieldsSettings(&this->automate->getField()->getPropetries(), false))
            return;
    }
    if (!this->simulating_window)
        simulating_window = new SimulatingForm(this, this->automate);
    //на случай, если добавлено новое состояние, а конфигурация уже была выбрана
    SingleCounter::getCounter().selectConfiguration(this->automate->getField()->getCurrentFieldsName());
    this->simulating_window->setWindowTitle(this->automate->getField()->getCurrentFieldsName());
    this->simulating_window->reSetPropetries();
    this->simulating_window->update();
    this->simulating_window->show();
    delete create_automate_window;
}

void Controller::closeSimulator()
{
    this->simulating_window->close();

    this->create_automate_window = new CreateAutomateForm(this, this->automate->getAlgorithm());
    QFileInfo file_name(this->current_path);
    this->create_automate_window->setWindowTitle(file_name.fileName());
    this->create_automate_window->show();
}
bool Controller::callFieldsSettings(SimulatingPropetries * propetries, bool has_field_already_initialized)
{
    int old_width(propetries->getWidth()), old_height(propetries->getHeight());
    Statement * old_default_statement = propetries->default_statements;
    SimulatingPropetriesForm form(this->automate->getAlgorithm(), *propetries);
    form.exec();
    if (!form.isOk())
        return false;
    if ((old_width != propetries->getWidth() || old_height != propetries->getHeight() ||
         old_default_statement != propetries->default_statements) || !has_field_already_initialized)
    {
        //(*this->automate->getField())->InitializeField(propetries->getWidth(), propetries->getHeight(),
         //                                           propetries->default_statements);
        this->automate->getField()->initializeField();
    }
    return true;
}
bool Controller::callSimulationSettings(SimulationPropetries * propetries)
{
    SimulationPropetriesForm form(*propetries);
    form.exec();
    if (!form.isOk())
        return false;
    return true;
}
bool Controller::openFieldsDistributingDialog()
{
    ChooseFieldDialog dialog(this->automate->getField());
    dialog.exec();
    if (!dialog.isOk())
        return false;
    if (!this->automate->getField()->isFieldInitialized())
    {
        while(!this->callFieldsSettings(&this->automate->getField()->getPropetries(), false)) {}
    }
}
