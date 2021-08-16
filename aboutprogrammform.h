#ifndef ABOUTPROGRAMMFORM_H
#define ABOUTPROGRAMMFORM_H

#include <QDialog>

namespace Ui {
class AboutProgrammForm;
}

class AboutProgrammForm : public QDialog
{
    Q_OBJECT

public:
    explicit AboutProgrammForm(QWidget *parent = nullptr);
    ~AboutProgrammForm();

private:
    Ui::AboutProgrammForm *ui;
};

#endif // ABOUTPROGRAMMFORM_H
