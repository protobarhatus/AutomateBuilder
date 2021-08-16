#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include "field.h"
#include "simulatingpropetries.h"

class Configuration
{
public:
    Configuration(Algorithm * algorithm);
    bool isInitialized();
    void initialize();
    void uninitialize();
    Field * getField();
    SimulatingPropetries & getPropetries();
private:
    Field field;
    SimulatingPropetries propetries;
    bool is_initialized = false;
};

#endif // CONFIGURATION_H
