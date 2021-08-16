#ifndef ADDRULEFORMCONTROLLER_H
#define ADDRULEFORMCONTROLLER_H
#include "addruleform.h"
#include <memory>
class Controller;
class LogicElement;
class Action;

class AddRuleFormController
{
public:
    AddRuleFormController(Controller * controller, QString condition, QString action,
                          QString second_action, bool is_global);
    void start();

    bool checkDataBeforeAccepting();
    void closeWithAcceptingData();

    QString getStrCondition();
    QString getStrAction();
    QString getStrSecondAction();
    bool isGlobal();
    bool isOK();
    std::shared_ptr<LogicElement> getCondition();
    std::shared_ptr<Action> getAction();
    std::shared_ptr<Action> getSecondAction();
private:
    Controller * controller;
    AddRuleForm form;
    QString str_condition;
    QString str_action;
    QString str_second_action;
    bool is_global;
    bool is_OK = false;
    std::shared_ptr<LogicElement> condition;
    std::shared_ptr<Action> action;
    std::shared_ptr<Action> second_action;
};

#endif // ADDRULEFORMCONTROLLER_H
