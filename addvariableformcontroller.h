#ifndef ADDVARIABLEFORMCONTROLLER_H
#define ADDVARIABLEFORMCONTROLLER_H
#include "addvariableform.h"
#include "memory"
class Controller;
class LogicElement;
class ValueElement;
class Automate;

class AddVariableFormController
{
public:

    AddVariableFormController(Controller * controller, Automate * automate);
    void start(QString name, QString str_value, VariableType type, VariableClass v_class);
    void closeWithAcceptingData();
    QString getName();
    VariableType getType();
    VariableClass getClass();
    std::shared_ptr<LogicElement> getLogicValue();
    std::shared_ptr<ValueElement> getNumericValue();
    bool checkDataBeforeAccepting();
    QString getFormula();
    bool isOK();
private:
    QString name;
    VariableType type;
    VariableClass v_class;
    bool dialog_result = false;
    std::shared_ptr<AddVariableForm> form;
    Controller * main_controller;
    std::shared_ptr<LogicElement> logic_value;
    std::shared_ptr<ValueElement> numeric_value;
    bool tryToBuildLogicFormula(QString formula);
    bool tryToBuildNumericFormula(QString formula);
    QString formula;
    bool is_by_formula;
    bool non_formula_logic_value;
    bool non_formula_numeric_value;
    Automate * automate;
};

#endif // ADDVARIABLEFORMCONTROLLER_H
