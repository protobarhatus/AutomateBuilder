#ifndef ADDSTATEMENTFORMCONTROLLER_H
#define ADDSTATEMENTFORMCONTROLLER_H
#include "addstatementform.h"
class Controller;

class AddStatementFormController
{
public:
    AddStatementFormController(Controller * controller, QString name, int number);
    AddStatementFormController(Controller * controller);
    void setImage(QPixmap pixmap);
    void setColor(QColor color);
    void start();
    bool isOK();

    QString getName();
    int getNumber();
    bool isGivenByColor();
    QPixmap getSprite();
    QColor getColor();
private:
    void loadImageButtonPressed();
    void changeColorButtonPressed();

    bool checkDataBeforeAccepting();
    void closeWithAcceptingData();
    AddStatementForm form;
    QString name;
    int number;
    bool is_given_by_color;
    bool has_choosen_representation = false;
    bool has_defined_number = false;
    QPixmap image;
    QColor color;
    bool dialog_result = false;
    Controller * main_controller;
    friend AddStatementForm;
};

#endif // ADDSTATEMENTFORMCONTROLLER_H
