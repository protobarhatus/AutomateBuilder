#ifndef STATEMENT_H
#define STATEMENT_H
#include<QtWidgets/QtWidgets>
#include"tqpixmap.h"


class Statement
{
public:

    Statement(QString name, int number, TQPixmap sprite);
    void setSprite(TQPixmap sprite);
    void setNumber(int number);
    void setName(QString name);
    TQPixmap getSprite();
    int getNumber();
    QString getName();
private:
    TQPixmap sprite;
    int number;
    QString name;

};

#endif // STATEMENT_H
