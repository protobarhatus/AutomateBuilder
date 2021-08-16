#ifndef PROGRAMMMANAGER_H
#define PROGRAMMMANAGER_H
class StartWindow;

class ProgrammManager
{
public:
    ProgrammManager();
    void start();

private:
    StartWindow * start_window;
};

#endif // PROGRAMMMANAGER_H
