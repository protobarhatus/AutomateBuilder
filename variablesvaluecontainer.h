#ifndef VARIABLESVALUECONTAINER_H
#define VARIABLESVALUECONTAINER_H
#include <vector>
#include <thread.h>
#include <QDebug>

#ifndef DEBUG
#include <concurrent_vector.h>

#endif
//хранит значения каждой из переменной, разделенные между потоками, выполняющимися из Field. Предполагается, что id потока
//принимает значения [0; threads.size) и совпадает с позицией необходимого значения в массиве. Он позволяет одной переменной
//служить нескольких потоках, безопасно работая одновременно в разных участках поля
template <typename ValueType>
class VariablesValueContainer
{
public:
    VariablesValueContainer() {}
    void setSize(int size)
    {
#ifndef DEBUG
        values.resize(size);
#endif
    }
    void setValue(ValueType value)
    {
#ifndef DEBUG
        values[Thread::currentId()] = value;
#endif
    }
    ValueType getValue() const
    {
#ifndef DEBUG
        return values[Thread::currentId()];
#endif
    }

private:
#ifndef DEBUG
    concurrency::concurrent_vector<ValueType> values;
#endif
};

#endif // VARIABLESVALUECONTAINER_H
