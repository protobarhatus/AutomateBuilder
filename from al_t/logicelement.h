#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H


class LogicElement
{
public:
    LogicElement();
    virtual bool getValue() const = 0;
    virtual ~LogicElement();
};


#endif // LOGICELEMENT_H
