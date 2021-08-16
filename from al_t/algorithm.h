#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<map>
#include<valuevariable.h>
#include<logicvariable.h>
#include<statement.h>

class Algorithm
{
public:
    Algorithm();

    void addLogicVariable(QString name, bool value);
    void addStatement(QString name, int number, TQPixmap sprite);

private:
    std::map<QString, LogicVariable> logic_variable_list;
    std::map<QString, ValueVariable> value_variables_list;
    std::map<QString, ValueVariable> global_variables_list;
    std::map<QString, Statement> statements_list;
    std::map<int, Statement*> statements_number_list;

};

#endif // ALGORITHM_H
