#ifndef ADDVARIABLEFORM_H
#define ADDVARIABLEFORM_H

#include <QWidget>
#include <QAbstractButton>
#include <QDialog>
enum VariableType
{
    LOGIC,
    VALUE
};
enum VariableClass
{
    GLOBAL,
    ITERATIVE
};
class AddVariableFormController;
namespace Ui {
class AddVariableForm;
}

class AddVariableForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddVariableForm(AddVariableFormController * controller, QString name, VariableType type, VariableClass v_class, QWidget *parent = nullptr);
    ~AddVariableForm();
    void setLogicValue(bool value);
    void setValue(int value);

private slots:
    void on_isLogicRadioButton_clicked();

    void on_isValueRadioButton_clicked();



    void on_OkCancelDialogBox_accepted();

    void on_OkCancelDialogBox_rejected();

private:
    Ui::AddVariableForm *ui;
    void setLogicType();
    void setValueType();
    friend AddVariableFormController;
    AddVariableFormController * controller;
    void setGuiToGrid();

};

#endif // ADDVARIABLEFORM_H
