#ifndef LOGICVARIABLE_H
#define LOGICVARIABLE_H
#include<QString>
#include"logicelement.h"
class LogicVariable : public LogicElement
{
public:
    LogicVariable(QString name, bool value);
    LogicVariable(QString name);
    virtual bool getValue() const override;

private:
    friend bool operator<(LogicVariable left, LogicVariable right);
    QString name;
    bool value;
};
bool operator<(LogicVariable left, LogicVariable right);
#endif // LOGICVARIABLE_H
