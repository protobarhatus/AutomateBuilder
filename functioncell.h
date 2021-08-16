#ifndef FUNCTIONCELL_H
#define FUNCTIONCELL_H
#include"valueelement.h"

class FieldDistributor;
class Algorithm;

class FunctionCell : public ValueElement
{
public:
    FunctionCell(QString name, int X, int Y, bool is_allowed, FieldDistributor * field);
    virtual int getValue() const override;
    virtual QString reBuildStringFormula() const override;
    //Не вызывать эту функцию вне предела Algorithm
    void setPermissibility(bool is_allowed);
    bool isAllowed();
    QString getDefinition();
    //по функционалу тоже самое, что и reBuildStringFormula, однако они различаются по смыслу и применяются в разных ситуациях
    QString getName();
    int getX() const;
    int getY() const;
    void setName(QString name);
    void setX(int X);
    void setY(int Y);
private:
    QString name;
    int X, Y;
    FieldDistributor * field;
    //Данное поле требуется только для режима создания автомата, во время симуляции изменять его не требуется
    bool is_allowed;
};

#endif // FUNCTIONCELL_H
