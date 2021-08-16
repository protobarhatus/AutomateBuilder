#ifndef ADDSTATEMENTFORM_H
#define ADDSTATEMENTFORM_H

#include <QDialog>
class AddStatementFormController;

namespace Ui {
class AddStatementForm;
}

class AddStatementForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddStatementForm(AddStatementFormController * controller, QWidget *parent = nullptr);
    ~AddStatementForm();
private slots:
    void on_LoadImageButton_clicked();

    void on_ChooseAColorButton_clicked();

    void on_OkCancelDialogBox_accepted();

    void on_OkCancelDialogBox_rejected();

private:
    void setGuiToGrid();

    Ui::AddStatementForm *ui;
    friend AddStatementFormController;
    AddStatementFormController * controller;
};

#endif // ADDSTATEMENTFORM_H
