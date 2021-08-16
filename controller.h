#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "QWidget"
#include "addvariableformcontroller.h"
class StartWindow;
class Automate;
class CreateAutomateForm;
class SimulatingForm;
class SimulatingPropetries;
class SimulationPropetries;
class Controller
{
public:
    Controller();
    bool createAutomateButtonPressed(QWidget * parent = nullptr);

    void addVariableButtonPressed();
    void changeVariableButtonPressed(QString variable);
    void deleteVariableButtonPressed(QString name);

    void addStatementButtonPressed();
    void changeStatementButtonPressed(int number);
    void deleteStatementButtonPressed(int number);

    void addRuleButtonPressed();
    void changeRuleButtonPressed(int number);
    void deleteRuleButtonPressed(int number);

    void addEnvironsFunctionButtonPressed();
    void changeEnvironsFunctionButtonPressed(QString name);
    void deleteEnvironsFunctionButtonPressed(QString name);

    void openSimulator();
    void closeSimulator();

    void start();
    //возвращает false, если действие отменено
    bool callFieldsSettings(SimulatingPropetries * propetries, bool has_field_already_initialized);
    bool callSimulationSettings(SimulationPropetries * propetries);
    Automate * getAutomate();
    bool isVariablesNameFree(QString name, VariableClass v_class);

    void saveAutomate();
    void saveAutomate(QString path);
    bool loadAutomate(QString path);
    void loadAutomateButtonPressed(QWidget * parent = nullptr);
    bool saveAsAutomateButtonPressed(QWidget * parent = nullptr);
    bool openFieldsDistributingDialog();
private:
    Automate * automate = nullptr;

    //windows
    StartWindow * start_window = nullptr;
    CreateAutomateForm * create_automate_window = nullptr;
    SimulatingForm * simulating_window = nullptr;
    void changeLogicVariable(QString name);
    void changeValueVariable(QString name);
    QString current_path;
};

#endif // CONTROLLER_H
