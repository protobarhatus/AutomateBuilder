#include "simulationpropetries.h"


SimulationPropetries::SimulationPropetries(int time, SimulationPropetries::Stop stop, int istep)
{
    this->stop_param = stop;
    this->time_between_iterations = time;
    this->step = istep;
}
void SimulationPropetries::dontStop()
{
    this->stop_param = STOP_DONT;
}
void SimulationPropetries::stopOnStep(int istep)
{
    this->stop_param = STOP_ON_STEP;
    this->step = istep;
}
void SimulationPropetries::stopEveryStep(int istep)
{
    this->stop_param = STOP_EVERY_STEPS;
    this->step = istep;
}
SimulationPropetries::Stop SimulationPropetries::getStopParam() const
{
    return this->stop_param;
}
int SimulationPropetries::getStep() const
{
    return this->step;
}
void SimulationPropetries::setTimeBetweenIterations(int time)
{
    this->time_between_iterations = time;
}
int SimulationPropetries::getTimeBetweenIterations() const
{
    return this->time_between_iterations;
}
