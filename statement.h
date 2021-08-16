#ifndef STATEMENT_H
#define STATEMENT_H
#include<QtWidgets/QtWidgets>



class Statement
{
public:

    Statement(QString name, int number);
    Statement(){}
    //преобразует цвет в пиксмап или изменяет размер sprite
    //на необходимый
    void getReadyToDrawing(int st_width, int st_height);
    void setSprite(QPixmap sprite);
    void setNumber(int number);
    void setName(QString name);
    void setColor(QColor color);
    const QPixmap & getSprite();
    int getNumber() const;
    QString getName() const;
    QColor getColor();
    bool isGivenByColor();
    const QPixmap & getGraphicalRepresentation()const;
    QPixmap  getSprite(int width, int height) const;
private:
    QPixmap graphical_representation;
    QPixmap sprite;
    int number;
    QString name;
    bool is_given_by_color;
    QColor color;
};

#endif // STATEMENT_H
