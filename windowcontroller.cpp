#include "windowcontroller.h"

WindowController::WindowController(Controller * icontroller, QWidget * iwindow)
{
    this->controller = icontroller;
    this->window = iwindow;
}
