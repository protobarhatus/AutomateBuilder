#include "startwindow.h"
#include "ui_startwindow.h"
#include "controller.h"
#include "QPixmap"
#include <QApplication>
#include <QFileDialog>

#include<QByteArray>
#include<QImage>
#include<QPainter>
#include<QPaintDevice>
#include<QBuffer>
StartWindow::StartWindow(Controller * icontroller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->controller = icontroller;
    this->ui->Logo->setText(QString(""));

    /*
    QByteArray bytearray;
    image = pixmap->toImage();
    QBuffer buffer(&bytearray);
    buffer.open (QIODevice::WriteOnly) ;
    image.save(&buffer, "png");
    bytearray = qCompress(bytearray, 9);

    QFile file("C:\\\\QT projects\\file.test");
    file.open(QIODevice::WriteOnly);
    file.write(bytearray, bytearray.length());
    file.close();

    QFile file2("C:\\\\QT projects\\file.test");
    file2.open(QIODevice::ReadOnly);
    bytearray = file2.read(file2.size());
    bytearray = qUncompress(bytearray);
    image.loadFromData((uchar *)bytearray.data(), bytearray.length());
    */




}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_CreateAutomat_clicked()
{

    this->controller->createAutomateButtonPressed(this);

}

void StartWindow::on_LoadAutomat_clicked()
{
    this->controller->loadAutomateButtonPressed(this);
}
