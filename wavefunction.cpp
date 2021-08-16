#include "wavefunction.h"
#include "valueelement.h"
#include "field.h"
#include "algorithm.h"
#include "fielddistributor.h"
WaveFunction::WaveFunction(Algorithm * alg, FieldDistributor * ifield)
{
    this->field = ifield;
    this->algorithm = alg;
    this->algorithm->addWaveFunction(this);
}
WaveFunction::~WaveFunction()
{
    this->algorithm->eraseWaveFunction(this->id);
}
void WaveFunction::setRadius(std::shared_ptr<ValueElement> rad)
{
    this->radius = rad;
}
void WaveFunction::calculateRadius()
{
    int new_radius = this->radius->getValue();
    if (new_radius != this->current_radius || this->has_environ_changed)
    {
        this->current_radius = new_radius;
        this->getEnvironsFunctions();
        this->has_environ_changed = false;
    }

}
void WaveFunction::getEnvironsFunctions()
{
    if (this->current_radius == 1)
        this->environs_functions = this->algorithm->getAllowedEnvironsFunctions();
    else
    {
        this->environs_functions.clear();
        (*this->field)->doWaveRelativelyToTheCentre(this->algorithm->getAllowedEnvironsFunctions(), this->current_radius,
                                                  [this](int x, int y) {

            this->environs_functions.push_back(std::make_shared<FunctionCell>("", x, y, true, this->field));
        });
    }

}
void WaveFunction::setItsNumber(int number)
{
    this->id = number;
}
void WaveFunction::environChanged()
{
    this->has_environ_changed = true;
}
