#ifndef SIMULATINGPROPETRIES_H
#define SIMULATINGPROPETRIES_H
class Statement;
class Algorithm;

class SimulatingPropetries
{
public:
    SimulatingPropetries(int width, int height, int cells_width, int cells_height);
    //сеттеры кидают исключения
    void setWidth(int width);
    void setHeight(int height);
    void setCellsWidth(int width);
    void setCellsHeight(int height);
    int getWidth();
    int getHeight();
    int getCellsWidth();
    int getCellsHeight();

    Statement * default_statements;

private:
    friend class SimulatingForm;
    int width;
    int height;
    int cells_width;
    int cells_height;
};

#endif // SIMULATINGPROPETRIES_H
