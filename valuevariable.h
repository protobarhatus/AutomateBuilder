#ifndef VALUEVARIABLE_H
#define VALUEVARIABLE_H
#include<QString>
#include"valueelement.h"
#include <memory>
#include <variablesvaluecontainer.h>
class Algorithm;
class FieldDistributor;

class ValueVariable : public ValueElement
{
public:
    ValueVariable(QString name, QString sformula, std::shared_ptr<ValueElement> formula);
    virtual int getValue() const override;
    //вернет собственное строковое отображение
    virtual QString reBuildStringFormula() const override;
    //декомпилирует исполнительные элементы в новую строку и запишет в поле string_formula. применяется, если имена некоторых
    //нетерминалов изменились
    void buildStringFormula();
    ValueVariable(QString name, bool is_global);
    ~ValueVariable() override;
    void setFormula(QString sformula, std::shared_ptr<ValueElement> formula);
    QString getStringFormula() const;
    void setName(QString name);
    void setGlobality(bool iis_global);
    QString getName();
    bool isGlobal();
    //собирает собственную формулу еще раз. если она оказывается невалидна - ставит соответствующую пометку и флаг
    void reCompileFormula(Algorithm * alg, FieldDistributor * field);
    bool isFormulaValid();
    void count();
    void amountOfThreadsChanged(int new_amount);
private:
    QString name;
    std::shared_ptr<ValueElement> formula;
    QString string_formula;
    int single_value;
    VariablesValueContainer<int> values;
    bool is_formula_valid = true;
    bool is_global;
};

#endif // VALUEVARIABLE_H
