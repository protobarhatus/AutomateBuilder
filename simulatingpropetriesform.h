#ifndef SIMULATINGPROPETRIESFORM_H
#define SIMULATINGPROPETRIESFORM_H

#include <QDialog>

namespace Ui {
class SimulatingPropetriesForm;
}
class SimulatingPropetries;
class Algorithm;

class SimulatingPropetriesForm : public QDialog
{
    Q_OBJECT

public:
    explicit SimulatingPropetriesForm(Algorithm * alg, SimulatingPropetries & propetries, QWidget *parent = nullptr);
    ~SimulatingPropetriesForm();
    bool isOk();

private slots:








    void on_OkCancelButtonBox_accepted();

    void on_OkCancelButtonBox_rejected();

private:
    Ui::SimulatingPropetriesForm *ui;
    SimulatingPropetries & propetries;
    void visualizeStatementsList();
    void displayAllData();
    void setGuiToTheGrid();
    bool checkDataBeforeAccepting();
    void closeWithAcceptingData();
    Algorithm * algorithm;
    bool is_ok = false;
};

#endif // SIMULATINGPROPETRIESFORM_H
