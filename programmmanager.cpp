#include "programmmanager.h"
#include "startwindow.h"
ProgrammManager::ProgrammManager()
{

}
void ProgrammManager::start()
{
    this->start_window = new StartWindow();
}
