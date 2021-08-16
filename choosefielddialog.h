#ifndef CHOOSEFIELDDIALOG_H
#define CHOOSEFIELDDIALOG_H

#include <QDialog>

namespace Ui {
class ChooseFieldDialog;
}
class FieldDistributor;
class QListWidgetItem;
class ChooseFieldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseFieldDialog(FieldDistributor * distributor, QWidget *parent = nullptr);
    ~ChooseFieldDialog();
    void update();
    bool isOk();
private slots:
    void on_addButton_clicked();

    void on_renameButton_clicked();

    void on_deleteButton_clicked();

    void on_okCancelDialogBox_accepted();

    void on_okCancelDialogBox_rejected();

    void on_configurationList_itemClicked(QListWidgetItem *item);

private:
    void setGuiToGrid();
    bool is_ok = false;
    void fillFieldsList();
    Ui::ChooseFieldDialog *ui;
    FieldDistributor * distributor;

};

#endif // CHOOSEFIELDDIALOG_H
