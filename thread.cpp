#include "thread.h"

Thread::Thread()
{
    this->is_launched.store(false);
}
void Thread::setMainFunction(std::function<void ()> function)
{
    this->main_function = function;
}
void Thread::setId(int id)
{
    this->identificator = id;
}
int Thread::currentId()
{
    return dynamic_cast<Thread*>(QThread::currentThread())->identificator;
}
int Thread::getId()
{
    return this->identificator;
}
void Thread::run()
{
    this->is_launched.store(true);
    this->main_function();
    this->is_launched.store(false);
}
void Thread::quit()
{
    this->is_launched.store(false);
}
bool Thread::isLaunched()
{
    return this->is_launched.load();
}
