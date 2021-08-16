#include "functionrand.h"
#include<random>
FunctionRand::FunctionRand()
{

}
void FunctionRand::setHigh(int high_border)
{
    this->high = high_border;
}
void FunctionRand::setLow(int low_border)
{
    this->low = low_border;
}
int FunctionRand::getValue() const
{
    return rand() % (this->high - this->low) + this->low;
}
