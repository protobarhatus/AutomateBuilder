#ifndef LOGICVARIABLE_H
#define LOGICVARIABLE_H
#include<QString>
#include"logicelement.h"
#include <memory>
#include <variablesvaluecontainer.h>
class Algorithm;
class FieldDistributor;

class LogicVariable : public LogicElement
{
public:
    LogicVariable(QString name, QString sformula, std::shared_ptr<LogicElement> formula);
    LogicVariable(QString name);
    virtual bool getValue() const override;
    //вернет собственное строковое отображение
    virtual QString reBuildStringFormula() const override;
    //декомпилирует исполнительные элементы в новую строку и запишет в поле string_formula. применяется, если имена некоторых
    //нетерминалов изменились
    void buildStringFormula();
    //за валидность формулы отвечает парсер
    void setFormula(QString sformula, std::shared_ptr<LogicElement> formula);
    QString getStringFormula() const;
    void setName(QString name);
    void setGlobality(bool is_global);
    bool isGlobal();
    QString getName();
    //собирает собственную формулу еще раз. если она оказывается невалидна - ставит соответствующую пометку и флаг
    //подобные ей функции в еще нескольких сущностях вызываются при удалении какого-либо элемента. Они ничего не изменяют
    //и их цель - проверить, осталась ли собственная формула валидна после удаления элемента, иначе говоря - нет ли в цепочке
    //формул удаленного элемента и, как, следствие, указателя, ссылающегося на удаленный участок.
    void reCompileFormula(Algorithm * alg, FieldDistributor * field);
    bool isFormulaValid();
    //получает и записывает значение по формуле
    void count();
    void amountOfThreadsChanged(int new_amount);
private:
    friend bool operator<(LogicVariable left, LogicVariable right);
    std::shared_ptr<LogicElement> formula;
    QString string_formula;
    QString name;
    bool is_formula_valid = true;
    bool is_global;
    bool single_value;
    //размер контейнера должен определяться после определения глобальности
    VariablesValueContainer<bool> values;
};
bool operator<(LogicVariable left, LogicVariable right);
#endif // LOGICVARIABLE_H
