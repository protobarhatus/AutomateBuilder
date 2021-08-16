#ifndef ADDENVIRONSFUNCTIONFORMCONTROLLER_H
#define ADDENVIRONSFUNCTIONFORMCONTROLLER_H
#include "addenvironsfunctionform.h"
class Controller;

class AddEnvironsFunctionFormController
{
public:
    AddEnvironsFunctionFormController(Controller * controller, QString name, int X, int Y, bool is_allowed);
    void start();
    bool checkDataBeforeAccepting();
    void closeWithAcceptingData();

    QString getName();
    int getX();
    int getY();
    bool isAllowed();
    bool isOk();
private:
    AddEnvironsFunctionForm form;
    Controller * controller;
    QString name;
    int X, Y;
    bool is_allowed;
    bool isOK = false;
};

#endif // ADDENVIRONSFUNCTIONFORMCONTROLLER_H
