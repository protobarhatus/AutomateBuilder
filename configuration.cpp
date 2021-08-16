#include "configuration.h"
#include "field.h"
Configuration::Configuration(Algorithm * alg) : propetries(SimulatingPropetries(1000, 1000, 100, 100))
{
    this->field.setAlgorithm(alg);
}
bool Configuration::isInitialized()
{
    return this->is_initialized;
}
void Configuration::initialize()
{

    this->field.InitializeField(propetries.getWidth(), propetries.getHeight(), propetries.default_statements);
    this->is_initialized = true;

}
void Configuration::uninitialize()
{
    this->is_initialized = false;
}
Field* Configuration::getField()
{
    return &this->field;
}
SimulatingPropetries& Configuration::getPropetries()
{
    return this->propetries;
}
