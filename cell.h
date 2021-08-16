#ifndef CELL_H
#define CELL_H
#include "statement.h"
#include "statementscounter.h"
class Cell
{
public:
    Cell();
    ~Cell();
    Cell & operator=(const Cell & cell);
    Statement * getStatement();
    void setStatement(Statement * statement);

private:

    Statement * statement = nullptr;

};

#endif // CELL_H
