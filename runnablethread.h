#ifndef RUNABLETHREAD_H
#define RUNABLETHREAD_H
#include <QRunnable>
#include <functional>
class RunnableThread : public QRunnable
{
public:
    RunnableThread();
    void setMainFunction(std::function<void ()> function);

private:
    std::function<void ()> main_function;
    //класс не отвечает за собственное id
    int id;
};

#endif // RUNABLETHREAD_H
