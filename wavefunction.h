#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H
#include <memory>
#include <vector>
class ValueElement;
class FieldDistributor;
class FunctionCell;
class Algorithm;
//Абстрактный класс для функций, задействующих волну (COUNT, COND_IN_R). Эти функции заранее получают набор функций окружения,
//работающие со всеми необходимыми им клетками. Во время выполнения, данный функции просто проходят по этому набору, не выполняя
//волну. Поэтому, радиус данных функций должен вычисляться в global-time.
class WaveFunction
{
public:
    WaveFunction(Algorithm * algorithm, FieldDistributor * field);
    ~WaveFunction();
    void setRadius(std::shared_ptr<ValueElement> radius);
    void calculateRadius();
    void environChanged();
protected:
    FieldDistributor * field;
    bool has_environ_changed = false;
    Algorithm * algorithm;
    //набор всех клеток, которые входят в область функции. При радиусе равном 1, будут равны Algorithm::allowed_environs_functions_vector
    std::vector<std::shared_ptr<FunctionCell>> environs_functions;
    //сохраняет радиус элемента для того, чтобы не переполучать набор функций окружения, если новый вычисленный радиус не
    //отличается от старого
    int current_radius = -1;//std::numeric_limits<int>::quiet_NaN();
    std::shared_ptr<ValueElement> radius;
private:
    //присваивается алгоритмом, и хранится для него же
    int id;
    void getEnvironsFunctions();
    friend Algorithm;
    void setItsNumber(int number);




};

#endif // WAVEFUNCTION_H
