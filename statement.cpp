#include "statement.h"

Statement::Statement(QString iname, int inumber)
{
    this->name = iname;
    this->number = inumber;
}
void Statement::setSprite(QPixmap isprite)
{
    this->sprite = isprite;
    this->is_given_by_color = false;
}
void Statement::setColor(QColor icolor)
{
    this->color = icolor;
    this->is_given_by_color = true;
}
void Statement::setNumber(int inumber)
{

    this->number = inumber;
}
void Statement::setName(QString iname)
{
    this->name = iname;
}
const QPixmap & Statement::getSprite()
{
    return this->sprite;
}
int Statement::getNumber() const
{
    return this->number;
}
QString Statement::getName() const
{
    return this->name;
}
bool Statement::isGivenByColor()
{
    return this->is_given_by_color;
}
QColor Statement::getColor()
{
    return this->color;
}
void Statement::getReadyToDrawing(int width, int height)
{
    this->graphical_representation = QPixmap(width, height);
    if (this->is_given_by_color)
    {
        this->graphical_representation.fill(this->color);
    }
    else
    {
        this->graphical_representation = this->sprite.scaled(
                    width, height);
    }
}
QPixmap  Statement::getSprite(int width, int height) const
{

    if (this->is_given_by_color)
    {
        QPixmap scaled_sprite = QPixmap(width, height);
        scaled_sprite.fill(this->color);
        return scaled_sprite;
    }
    else
    {
        return this->sprite.scaled(width, height);
    }
}
const QPixmap & Statement::getGraphicalRepresentation() const
{
    return this->graphical_representation;
}
