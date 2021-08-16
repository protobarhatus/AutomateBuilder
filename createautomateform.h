#ifndef CREATEAUTOMATEFORM_H
#define CREATEAUTOMATEFORM_H

#include <QMainWindow>
class Controller;
class Algorithm;
namespace Ui {
class CreateAutomateForm;
}

class CreateAutomateForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateAutomateForm(Controller * controller, Algorithm * algorithm, QWidget *parent = nullptr);
    ~CreateAutomateForm();
    void update();
    void setAlgorithm(Algorithm * algorithm);
private slots:
    void on_add_variable_button_clicked();

    void on_change_variable_button_clicked();

    void on_delete_variable_button_clicked();

    void on_add_statement_button_clicked();

    void on_change_statement_button_clicked();

    void on_delete_statement_button_clicked();

    void on_add_rule_button_clicked();

    void on_change_rule_button_clicked();

    void on_delete_rule_button_clicked();

    void on_add_environs_function_buton_clicked();

    void on_change_environs_function_button_clicked();

    void on_delete_environs_function_button_clicked();

    void on_ReadyButton_clicked();

    void on_saveAction_triggered();

    void on_openAction_triggered();

    void on_saveAsAction_triggered();

    void on_Help_triggered();

    void on_aboutProgrammAction_triggered();

private:
    Ui::CreateAutomateForm *ui;
    Controller * controller;
    Algorithm * algorithm;
    void setGuiToGrid();
    void displayVariables();
    void displayStatements();
    void displayRules();
    void displayEnvironsFunction();

};

#endif // CREATEAUTOMATEFORM_H
