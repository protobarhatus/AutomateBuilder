#include "runnablethread.h"

RunnableThread::RunnableThread()
{

}
void RunnableThread::setMainFunction(std::function<void ()> function)
{
    this->main_function = function;
}
