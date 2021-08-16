#ifndef ADDRULEFORM_H
#define ADDRULEFORM_H

#include <QDialog>
class AddRuleFormController;
namespace Ui {
class AddRuleForm;
}

class AddRuleForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddRuleForm(AddRuleFormController * controller, QString condition, QString action,
                         QString second_action, bool is_global, QWidget *parent = nullptr);
    ~AddRuleForm();

private slots:
    void on_OkCancelButtonBox_accepted();
    void on_OkCancelButtonBox_rejected();
private:
    Ui::AddRuleForm *ui;
    AddRuleFormController * controller;
    friend AddRuleFormController;
    void setGuiToGrid();
};

#endif // ADDRULEFORM_H
