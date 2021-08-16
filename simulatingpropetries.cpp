#include "simulatingpropetries.h"
#include <QString>
SimulatingPropetries::SimulatingPropetries(int iwidth, int iheight, int icells_width, int icells_height) :
    width(iwidth), height(iheight), cells_width(icells_width), cells_height(icells_height)
{

}
void SimulatingPropetries::setWidth(int iwidth)
{
    if (iwidth <= 0)
        throw QString("Ширина поля должна быть больше нуля");
    this->width = iwidth;
}
void SimulatingPropetries::setHeight(int iheight)
{
    if (iheight <= 0)
        throw QString("Высота поля должна быть больше нуля");
    this->height = iheight;
}
void SimulatingPropetries::setCellsWidth(int iwidth)
{
    if (iwidth <= 0)
        throw QString("Ширина клетки должна быть больше нуля");
    this->cells_width = iwidth;
}
void SimulatingPropetries::setCellsHeight(int iheight)
{
    if (iheight <= 0)
        throw QString ("Высота клетки должна быть больше нуля");
    this->cells_height = iheight;
}
int SimulatingPropetries::getWidth()
{
    return this->width;
}
int SimulatingPropetries::getHeight()
{
    return this->height;
}
int SimulatingPropetries::getCellsWidth()
{
    return this->cells_width;
}
int SimulatingPropetries::getCellsHeight()
{
    return this->cells_height;
}
