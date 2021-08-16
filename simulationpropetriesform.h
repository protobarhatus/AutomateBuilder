#ifndef SIMULATIONPROPETRIESFORM_H
#define SIMULATIONPROPETRIESFORM_H

#include <QDialog>

namespace Ui {
class SimulationPropetriesForm;
}
class SimulationPropetries;
class SimulationPropetriesForm : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationPropetriesForm(SimulationPropetries & propetries, QWidget *parent = nullptr);
    ~SimulationPropetriesForm();
    bool isOk();
private slots:

    void on_stopSimulationCheckBox_stateChanged(int arg1);

    void on_onStepRadioButton_toggled(bool checked);

    void on_everyStepRadioButton_toggled(bool checked);

    void on_okCancelButtonBox_accepted();

    void on_okCancelButtonBox_rejected();

private:
    bool is_ok = false;
    Ui::SimulationPropetriesForm *ui;
    SimulationPropetries & propetries;
    bool checkDataBeforeAccepting();
    void closeWithAcceptingData();
    void setGuiToGrid();
};

#endif // SIMULATIONPROPETRIESFORM_H
