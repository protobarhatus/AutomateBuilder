#include "aboutprogrammform.h"
#include "ui_aboutprogrammform.h"

AboutProgrammForm::AboutProgrammForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutProgrammForm)
{
    ui->setupUi(this);
}

AboutProgrammForm::~AboutProgrammForm()
{
    delete ui;
}
