#include "drawingfield.h"
#include "QPainter"
#include "QMouseEvent"
DrawingField::DrawingField(QWidget *parent) : QWidget(parent)
{

}
void DrawingField::setFunctionToDraw(std::function<void (QPainter & painter)> function)
{
    this->function_to_draw = std::move(function);
}
void DrawingField::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    this->function_to_draw(painter);

}
void DrawingField::mousePressEvent(QMouseEvent * event)
{
    this->last_x = event->x();
    this->last_y = event->y();
    this->mouse_pressed_function(event);

}
void DrawingField::mouseMoveEvent(QMouseEvent * event)
{
    this->mouse_moved_event(event, last_x, last_y);
    this->last_x = event->x();
    this->last_y = event->y();
}
void DrawingField::mouseReleaseEvent(QMouseEvent * event)
{
    this->mouse_released_event(event);
}
void DrawingField::setMousePressedFunction(std::function<void (QMouseEvent *)> function)
{
    this->mouse_pressed_function = function;
}
void DrawingField::setMouseMovedFunction(std::function<void (QMouseEvent *, int, int)> function)
{
    this->mouse_moved_event = function;
}
void DrawingField::setMouseReleasedFunction(std::function<void (QMouseEvent *)> function)
{
    this->mouse_released_event = function;
}
void DrawingField::wheelEvent(QWheelEvent * event)
{
    this->wheel_function(event);
}
void DrawingField::setWheelFunction(std::function<void (QWheelEvent *)> function)
{
    this->wheel_function = function;
}
