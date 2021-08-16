#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include "controller.h"
#include <QImage>
namespace Ui {
class StartWindow;
}

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartWindow(Controller * controller, QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_CreateAutomat_clicked();

    void on_LoadAutomat_clicked();

private:
    Ui::StartWindow *ui;
    Controller * controller;
};

#endif // STARTWINDOW_H
