#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "QString"
#include "algorithm.h"
#include "fielddistributor.h"

class Automate
{
public:
    Automate(bool create_empty = false);
    void createAutomateFile(QString path);
    void saveAutomate(QString path);
    Algorithm * getAlgorithm();
    FieldDistributor * getField();

    static bool isVariableNameCorrectlyWritten(QString name);
    static bool isEnvironsFunctionNameCorrectlyWritten(QString name);
    void compliteOneStepOfSimulation();

private:

   Algorithm algorithm;
   FieldDistributor field;
};

#endif // AUTOMATE_H
