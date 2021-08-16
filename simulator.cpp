#include "simulator.h"
#include "field.h"
#include "simulatingform.h"
#include "ctime"
#include "automate.h"
#include "fielddistributor.h"

Simulator::Simulator(Automate * iautomate, FieldDistributor * ifield, SimulatingForm * iform)
{
    this->field = ifield;
    this->form = iform;
    this->automate = iautomate;
    this->is_step_compliting.store(false);
}
Simulator::Simulator(const Simulator & copy)
{
    this->is_on_pause = copy.is_on_pause;
    this->has_simulation_began = copy.has_simulation_began;
    this->is_step_compliting.store(false);
    this->field = copy.field;
    this->automate = copy.automate;
    this->form = copy.form;
    this->step = copy.step;

}
void Simulator::start(SimulationPropetries propetries)
{
    if (!this->is_on_pause)
        (*this->field)->launch();
    auto simulate = [this, propetries]()
    {

        this->has_simulation_began = true;
        this->is_on_pause = false;
        time_t iteration_start;
        int last_stopped_step = this->step;

        while(!is_on_pause && this->has_simulation_began)
        {
            iteration_start = clock();
            this->is_step_compliting.store(true);
            ++this->step;
            //qDebug() << "\n\nstarting the step, " << this->step;
            this->automate->compliteOneStepOfSimulation();
           // qDebug() << "finished";
            this->is_step_compliting.store(false);
            while(clock() - iteration_start < propetries.getTimeBetweenIterations()) {}            
            emit this->form->dataChanged();
            if (propetries.getStopParam() == SimulationPropetries::STOP_ON_STEP)
            {
                if (this->step == propetries.getStep())
                {
                    last_stopped_step = this->step;
                    this->pause();
                }
            }
            if (propetries.getStopParam() == SimulationPropetries::STOP_EVERY_STEPS)
            {
                if (this->step - last_stopped_step == propetries.getStep())
                {
                    last_stopped_step = this->step;
                    this->pause();
                }
            }

        }
    };

    this->thread = std::thread(simulate);
    this->thread.detach();
}
void Simulator::pause()
{
    if (this->has_simulation_began)
        this->is_on_pause = true;
}
void Simulator::stop()
{
    this->has_simulation_began = false;
    this->is_on_pause = false;
    while (this->is_step_compliting) {}
    (*this->field)->reset();
    this->step = 0;
    this->form->update();
}
unsigned long long int Simulator::getStep()
{
    return this->step;
}
bool Simulator::isOnPause()
{
    return this->is_on_pause;
}
