#ifndef DRAWINGFIELD_H
#define DRAWINGFIELD_H

#include <QWidget>
#include <functional>
//этот класс, впринципе, универсален. представляет собой поле, которое рисует на себе лямбдой
class DrawingField : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingField(QWidget *parent);
    void setFunctionToDraw(std::function<void (QPainter & painter)> function_to_draw);
    virtual void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);
    void setMousePressedFunction(std::function<void (QMouseEvent * event)> function);
    void setMouseMovedFunction(std::function<void (QMouseEvent * event, int last_x, int last_y)> function);
    void setMouseReleasedFunction(std::function<void (QMouseEvent * event)> function);
    void setWheelFunction(std::function<void (QWheelEvent * event)> function);
signals:

public slots:

private:
    std::function<void (QPainter & painter)> function_to_draw = [](QPainter & painter){Q_UNUSED(painter)};
    std::function<void (QMouseEvent * event)> mouse_pressed_function = [](QMouseEvent * event){Q_UNUSED(event)};
    std::function<void (QMouseEvent * event, int last_x, int last_y)> mouse_moved_event =
            [](QMouseEvent * event, int last_x, int last_y){Q_UNUSED(event) Q_UNUSED(last_x) Q_UNUSED(last_y)};
    std::function<void (QMouseEvent * event)> mouse_released_event = [](QMouseEvent * event){Q_UNUSED(event)};
    int last_x, last_y;
    std::function<void (QWheelEvent * event)> wheel_function = [](QWheelEvent * event){Q_UNUSED(event)};

};

#endif // DRAWINGFIELD_H
