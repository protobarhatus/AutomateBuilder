#ifndef SIMULATIONPROPETRIES_H
#define SIMULATIONPROPETRIES_H


class SimulationPropetries
{
public:
    enum Stop
    {
        STOP_DONT,
        STOP_ON_STEP,
        STOP_EVERY_STEPS
    };
    SimulationPropetries(int time_between_iterations, Stop stop_params, int step);
    void dontStop();
    void stopOnStep(int step);
    void stopEveryStep(int step);
    Stop getStopParam() const;
    int getStep() const;
    void setTimeBetweenIterations(int time);
    int getTimeBetweenIterations() const;
private:
    int time_between_iterations;

    int step;
    Stop stop_param;
};

#endif // SIMULATIONPROPETRIES_H
