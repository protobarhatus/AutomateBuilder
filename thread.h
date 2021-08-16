#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <functional>
#include <atomic>
class Thread : public QThread
{
public:
    Thread();
    void setMainFunction(std::function<void ()> function);
    void setId(int id);
    static int currentId();
    int getId();
    void run();
    bool isLaunched();
private slots:
    void quit();
private:
    std::function<void ()> main_function;
    int identificator;
    std::atomic_bool is_launched;
};

#endif // THREAD_H
