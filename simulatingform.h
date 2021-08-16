#ifndef SIMULATINGFORM_H
#define SIMULATINGFORM_H

#include <QMainWindow>
#include <QPainter>
#include "simulatingpropetries.h"
#include "simulationpropetries.h"
#include "simulator.h"
#include "QMutex"
namespace Ui {
class SimulatingForm;
}
class Algorithm;
class FieldDistributor;
class Controller;
class Automate;

#include "drawingfield.h"
class SimulatingForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulatingForm(Controller * controller, Automate * automate,QWidget *parent = nullptr);
    ~SimulatingForm();
    void paintEvent(QPaintEvent * event);
    void reSetPropetries();
    void resizeEvent(QResizeEvent * event);
public slots:
    void update();
signals:
    void dataChanged();
private slots:
    void on_launchButton_clicked();

    void on_backButton_clicked();

    void on_flushButton_clicked();

    void on_Field_triggered();

    void on_toCenterButton_clicked();

    void on_Simulation_triggered();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();


    void on_configurationsAction_triggered();

    void on_editModeCheckBox_stateChanged(int arg1);

    void on_pauseButton_clicked(bool checked);

    void on_editModeCheckBox_toggled(bool checked);

private:
    Ui::SimulatingForm *ui;
    Algorithm * algorithm;
    FieldDistributor * field;
    Automate * automate;
    Controller * controller;
    DrawingField * drawing_field;
    SimulatingPropetries propetries;
    SimulationPropetries simulation_propetries;
    Simulator simulator;
    double scroll_x = 0, scroll_y = 0;
    double scale_coefficient = 0.5;
    QPen lines_pen;


    void setLinesColor(int red, int green, int blue);
    void initializeDrawingField();
    //описывают лямбда-функции и передает их в drawing_field
    void setDrawingFunction();
    void setMouseMovedFunction();
    void setWheelFunction();
    void setMousePressedFunction();
    void setMouseReleasedFunction();

    void fillStatementsList();
    //относит. координаты курсора по отношению к полю (значения [0;1])
    double getRelativelyCursorX(int cursor_x);
    double getRelativelyCursorY(int cursor_y);
    bool has_mouse_moved;
    bool is_drawing_blocked = false;
    bool has_began_simulation = false;
};

#endif // SIMULATINGFORM_H
