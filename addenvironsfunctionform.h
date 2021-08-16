#ifndef ADDENVIRONSFUNCTIONFORM_H
#define ADDENVIRONSFUNCTIONFORM_H

#include <QDialog>

namespace Ui {
class AddEnvironsFunctionForm;
}

class AddEnvironsFunctionFormController;

class AddEnvironsFunctionForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddEnvironsFunctionForm(AddEnvironsFunctionFormController * controller, QWidget *parent = nullptr);
    ~AddEnvironsFunctionForm();

private slots:
    void on_OkCancelButtonBox_accepted();

    void on_OkCancelButtonBox_rejected();

private:
    Ui::AddEnvironsFunctionForm *ui;
    friend AddEnvironsFunctionFormController;
    AddEnvironsFunctionFormController * controller;
    void setGuiToTheGrid();
};

#endif // ADDENVIRONSFUNCTIONFORM_H
