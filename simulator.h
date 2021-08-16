#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "simulationpropetries.h"
#include "thread.h"
#include <thread>
class SimulatingForm;
class FieldDistributor;
class Automate;
//выполняет симуляцию
class Simulator
{
public:
    Simulator(Automate * automate, FieldDistributor * field, SimulatingForm * form);
    Simulator(const Simulator & copy);
    void start(SimulationPropetries propetries);
    void pause();
    void stop();
    unsigned long long int getStep();
    bool isOnPause();
private:

    bool is_on_pause = false;
    bool has_simulation_began = false;
    std::atomic_bool is_step_compliting;
    FieldDistributor * field;
    Automate * automate;
    SimulatingForm * form;
    unsigned long long int step = 0;
    std::thread thread;
};

#endif // SIMULATOR_H
