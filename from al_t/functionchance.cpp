#include "functionchance.h"
#include "random"
FunctionChance::FunctionChance()
{

}
bool FunctionChance::getValue() const
{
    return rand() % 100 < chance;
}
