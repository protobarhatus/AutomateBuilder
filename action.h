#ifndef ACTION_H
#define ACTION_H
#include<memory>
#include<vector>
#include <QString>
class ActionElement;
class Algorithm;
class FieldDistributor;

class Action
{
public:
    Action();
    void addActionElement(std::shared_ptr<ActionElement> action_element, QString string_action_element);
    void doAction();
    QString buildStringFormula();
    //возращает false, если формула невалидна. остальные такие функции невозвращают ничего, однако эта должна дать понять rule, что
    //action невалидно
    bool reCompileStringFormula(Algorithm * alg, FieldDistributor * field);
    QString getStringFormula();
private:
    std::vector<std::shared_ptr<ActionElement>> action_elements;
    QString string_formula;
};

#endif // ACTION_H
