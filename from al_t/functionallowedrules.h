#ifndef FUNCTIONALLOWEDRULES_H
#define FUNCTIONALLOWEDRULES_H
#include"valueelement.h"

class AlgorithmInterface;
class FunctionAllowedRules : public ValueElement
{
public:
    FunctionAllowedRules();
    AlgorithmInterface * algorithm;
};

#endif // FUNCTIONALLOWEDRULES_H
