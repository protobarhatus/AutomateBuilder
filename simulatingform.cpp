#include "simulatingform.h"
#include "ui_simulatingform.h"
#include "algorithm.h"
#include "field.h"
#include "controller.h"
#include "automate.h"

#include "simulatingpropetriesform.h"
#include "somedataworks.h"

#include "QMouseEvent"
#include "QWheelEvent"

#include"statementscounter.h"
#include "fielddistributor.h"
SimulatingForm::SimulatingForm(Controller * icontroller, Automate * iautomate, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulatingForm),
    propetries(iautomate->getField()->getPropetries()),
    simulation_propetries(SimulationPropetries(50, SimulationPropetries::STOP_DONT, 0)),
    simulator(Simulator(iautomate, iautomate->getField(), this))
{
    ui->setupUi(this);
    connect(this, SIGNAL(dataChanged()), this, SLOT(update()), Qt::ConnectionType::BlockingQueuedConnection);
    this->algorithm = iautomate->getAlgorithm();
    this->field = iautomate->getField();
    this->automate = iautomate;
    this->controller = icontroller;


    this->algorithm->prepareAllStatementsToDraw(this->propetries.cells_width, this->propetries.cells_height);
    this->setLinesColor(64, 66, 68);
    this->initializeDrawingField();
    this->setDrawingFunction();
    this->setMouseMovedFunction();
    this->setWheelFunction();
    this->fillStatementsList();
    this->setMousePressedFunction();
    this->setMouseReleasedFunction();

    this->ui->statusbar->hide();

}

SimulatingForm::~SimulatingForm()
{
    delete ui;
    delete this->drawing_field;

}
void SimulatingForm::setLinesColor(int red, int green, int blue)
{
    QColor color;
    color.setRed(red);
    color.setGreen(green);
    color.setBlue(blue);
    this->lines_pen = QPen(color);
}
void SimulatingForm::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
   // QPainter painter(this->ui->mainFieldLabel);
 //   painter.setPen(Qt::blue);
  //  painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
 //   painter.drawLine(0, 0, 500, 500);
}
void SimulatingForm::initializeDrawingField()
{
    this->drawing_field = new DrawingField(this);

    //this->setCentralWidget(this->drawing_field);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, getColor(195, 195, 195));
    this->drawing_field->setAutoFillBackground(true);
    this->drawing_field->setPalette(pal);
    this->drawing_field->setGeometry(0, this->ui->statementsList->y() + this->menuBar()->height(),
                                     this->ui->statementsList->x(),
                                     this->ui->statementsList->height());

    this->drawing_field->show();

}
/*rt[z].x = (width / 2 + scroll_x) - (center - z) * cwidth * scale_coefficient
 *
 *
 */
//TODO: добавить масштаб в расчеты
void SimulatingForm::setDrawingFunction()
{

    this->drawing_field->setFunctionToDraw(
                [this](QPainter & painter)->void {
        if (this->is_drawing_blocked)
            return;
        //да, тут преобразования в целочисленный тип, однако, мы работает с дикретными пикселями и приходится мириться
        int x_center = int(this->drawing_field->width() / 2 + this->scroll_x * this->scale_coefficient);
        int y_center = int(this->drawing_field->height() / 2 + this->scroll_y * this->scale_coefficient);
        int scaled_cells_width = int(this->propetries.cells_width * this->scale_coefficient);
        int scaled_cells_height = int(this->propetries.cells_height * this->scale_coefficient);
        if (scaled_cells_width <= 1 || scaled_cells_height <= 1)
            return;
        painter.setPen(this->lines_pen);
        //координаты клетки, которая рисуется непосредственно справа снизу от центральных линий
        QPoint coordinate_of_central_cell (this->propetries.width / 2, this->propetries.height / 2);
        //координата наиболее левой верхней клетки, которая поместится в поле рисования
        QPoint coordinate_of_left_upper_cell(coordinate_of_central_cell.x() - divideWithRoundingToBigger(x_center,
              scaled_cells_width), coordinate_of_central_cell.y() - divideWithRoundingToBigger(y_center, scaled_cells_height));
        //координата наиболее нижней правой клетки, которая поместится в поле рисования
        QPoint coordinate_of_right_lower_cell(coordinate_of_central_cell.x() + divideWithRoundingToBigger(
            this->drawing_field->width() - x_center, scaled_cells_width) - 1, coordinate_of_central_cell.y() +
             divideWithRoundingToBigger(this->drawing_field->height() - y_center, scaled_cells_height) - 1);

        for (int x = coordinate_of_left_upper_cell.x(); x <= coordinate_of_right_lower_cell.x(); ++x)
        {
            for (int y = coordinate_of_left_upper_cell.y(); y <= coordinate_of_right_lower_cell.y(); ++y)
            {
                if (!(*this->field)->isInField(x, y))
                    continue;
                int dr_x(x_center - (coordinate_of_central_cell.x() - x) * scaled_cells_width),
                        dr_y(y_center - (coordinate_of_central_cell.y() - y) * scaled_cells_height);
                const QPixmap & sprite = (*this->field)->getStatementOfCell(x, y)->getGraphicalRepresentation();
                painter.drawPixmap(dr_x, dr_y, scaled_cells_width, scaled_cells_height,
                                   sprite);
                painter.drawRect(dr_x, dr_y, scaled_cells_width, scaled_cells_height);
            }
        }

        painter.setPen(QPen(std::move(getColor(255, 255, 255)), 3));
        painter.drawLine(x_center, 0, x_center, this->drawing_field->height());
        painter.drawLine(0, y_center, this->drawing_field->width(), y_center);
    });
}
void SimulatingForm::setMouseMovedFunction()
{
    this->drawing_field->setMouseMovedFunction([this](QMouseEvent * event, int last_x, int last_y)->void {
        this->has_mouse_moved = true;
        this->scroll_x += (event->x() - last_x) / this->scale_coefficient;

        this->scroll_y += (event->y() - last_y) / this->scale_coefficient;
        this->update();
    });
}
void SimulatingForm::setWheelFunction()
{
    this->drawing_field->setWheelFunction([this](QWheelEvent * event)->void {

        int x_center = int(this->drawing_field->width() / 2 + this->scroll_x * this->scale_coefficient);
        int y_center = int(this->drawing_field->height() / 2 + this->scroll_y * this->scale_coefficient);

        int field_scaled_width = this->propetries.width * int(this->propetries.cells_width * this->scale_coefficient);
        int field_scaled_height = this->propetries.height * int(this->propetries.cells_height * this->scale_coefficient);

        double x_distance = double(x_center - event->x()) / double(field_scaled_width);
        double y_distance = double(y_center - event->y()) / double(field_scaled_height);

        this->scale_coefficient *= (1 + (double(event->delta()) / 5000.0 ));

        field_scaled_width = this->propetries.width * int(this->propetries.cells_width * this->scale_coefficient);
        field_scaled_height = this->propetries.height * int(this->propetries.cells_height * this->scale_coefficient);

        this->scroll_x = (event->x() + (x_distance) * field_scaled_width -
                (this->drawing_field->width() / 2)) / this->scale_coefficient;
        this->scroll_y = (event->y() + (y_distance) * field_scaled_height -
                (this->drawing_field->height() / 2)) / this->scale_coefficient;

        this->algorithm->prepareAllStatementsToDraw(this->propetries.cells_width * scale_coefficient,
                                                    this->propetries.cells_height * scale_coefficient);
        this->update();
    });
}
void SimulatingForm::fillStatementsList()
{
    SingleCounter & counter = SingleCounter::getCounter();
    int current_row = this->ui->statementsList->currentRow();
    this->ui->statementsList->clear();
    for (auto &it : this->algorithm->getStatementsList())
    {
        QString number_in_string, amount_in_string;
        number_in_string.setNum(it.first);
        amount_in_string.setNum(counter.getAmountOfElements(it.first));
        QListWidgetItem * item = new QListWidgetItem(QIcon(it.second->getSprite(this->ui->statementsList->iconSize().width(),
                                                                                this->ui->statementsList->iconSize().height())),
                                                     "(" + number_in_string + ") " + it.second->getName() + ": " +
                                                     amount_in_string);
        item->setWhatsThis(number_in_string);
        this->ui->statementsList->addItem(item);
    }
    this->ui->statementsList->setCurrentRow(current_row);
}
void SimulatingForm::setMousePressedFunction()
{
    this->drawing_field->setMousePressedFunction([this](QMouseEvent * event) {
        Q_UNUSED(event)
        this->has_mouse_moved = false;
    });
}
void SimulatingForm::setMouseReleasedFunction()
{
    this->drawing_field->setMouseReleasedFunction([this](QMouseEvent * event) {
        if (this->has_mouse_moved)
            return;
        if (this->ui->statementsList->currentRow() == -1)
            return;
        if (!this->ui->editModeCheckBox->isChecked())
            return;
        //относит. координаты курсора по отношению к полю (значения [0;1])
        double relatively_cursor_x = this->getRelativelyCursorX(event->x());
        double relatively_cursor_y = this->getRelativelyCursorY(event->y());
        //qDebug() << relatively_cursor_x << " : " << relatively_cursor_y;
        int xcell = int(relatively_cursor_x * propetries.width),
                ycell = int(relatively_cursor_y * propetries.height);
        (*this->field)->setStatement(xcell, ycell, this->algorithm->getStatement(
                                      this->ui->statementsList->currentItem()->whatsThis().toInt()));
        this->update();

    });
}
double SimulatingForm::getRelativelyCursorX(int cursor_x)
{
    int x_center = int(this->drawing_field->width() / 2 + this->scroll_x * this->scale_coefficient);
    int scaled_cells_width = int(this->propetries.cells_width * this->scale_coefficient);
    int field_graphical_lefttop_x = x_center - (this->propetries.width / 2) * scaled_cells_width;
    int field_graphical_rightbot_x = x_center + divideWithRoundingToBigger(this->propetries.width, 2) * scaled_cells_width;

    return double(cursor_x - field_graphical_lefttop_x) / (field_graphical_rightbot_x - field_graphical_lefttop_x);
}
double SimulatingForm::getRelativelyCursorY(int cursor_y)
{
    int y_center = int(this->drawing_field->height() / 2 + this->scroll_y * this->scale_coefficient);
    int scaled_cells_height = int(this->propetries.cells_height * this->scale_coefficient);
    int field_graphical_lefttop_y = y_center - (this->propetries.height / 2) * scaled_cells_height;
    int field_graphical_rightbox_y = y_center + divideWithRoundingToBigger(this->propetries.height, 2) * scaled_cells_height;
    return double(cursor_y - field_graphical_lefttop_y) / (field_graphical_rightbox_y - field_graphical_lefttop_y);
}
void SimulatingForm::on_launchButton_clicked()
{
    this->simulator.start(this->simulation_propetries);
    this->ui->pauseButton->setChecked(false);
    this->ui->editModeCheckBox->setChecked(false);
    this->has_began_simulation = true;
}
void SimulatingForm::update()
{
    this->drawing_field->repaint();
    this->fillStatementsList();

}

void SimulatingForm::on_backButton_clicked()
{
    if (!this->has_began_simulation)
        this->controller->closeSimulator();
    else
        QMessageBox::critical(this, "Невозможно", "Сначала завершите симуляцию");
}

void SimulatingForm::on_flushButton_clicked()
{
    if (!this->ui->editModeCheckBox->isChecked())
        return;
    (*this->field)->clear();
    this->update();
}

void SimulatingForm::on_Field_triggered()
{
    if (this->has_began_simulation)
    {
        QMessageBox::critical(this, "Невозможно", "Сначала завершите конфигурацию");
        return;
    }
    this->controller->callFieldsSettings(&this->field->getPropetries(), true);
    this->reSetPropetries();
    this->update();
}

void SimulatingForm::on_toCenterButton_clicked()
{
    this->scroll_x = 0.0;
    this->scroll_y = 0.0;
    this->update();
}

void SimulatingForm::on_Simulation_triggered()
{
    this->controller->callSimulationSettings(&this->simulation_propetries);
}

void SimulatingForm::on_pauseButton_clicked()
{

    this->simulator.pause();
    if (this->has_began_simulation)
    {
        this->ui->pauseButton->setChecked(true);
        this->ui->editModeCheckBox->setChecked(false);
    }
}

void SimulatingForm::on_stopButton_clicked()
{
    this->ui->pauseButton->setChecked(false);
    this->simulator.stop();
    this->ui->editModeCheckBox->setChecked(true);
    this->has_began_simulation = false;
    this->update();
}

void SimulatingForm::on_configurationsAction_triggered()
{
    if (this->has_began_simulation)
    {
        QMessageBox::critical(this, "Невозможно", "Сначала завершите конфигурацию");
        return;
    }
    this->is_drawing_blocked = true;
    this->controller->openFieldsDistributingDialog();
    this->reSetPropetries();
    this->is_drawing_blocked = false;
    this->scroll_x = 0;
    this->scroll_y = 0;
    this->setWindowTitle(this->field->getCurrentFieldsName());
    this->update();
}
void SimulatingForm::reSetPropetries()
{
    this->propetries = this->field->getPropetries();
}
void SimulatingForm::resizeEvent(QResizeEvent * event)
{
    if (event->oldSize().width() == -1)
        return;


    this->ui->statementsList->setGeometry(this->width() - this->ui->statementsList->width(),
                                          this->ui->UpperPanelFoneLabel->y() + this->ui->UpperPanelFoneLabel->height(),
                                          this->ui->statementsList->width(),
                                          this->height() - this->ui->UpperPanelFoneLabel->height() -
                                          this->ui->menubar->y());
    this->drawing_field->setGeometry(0, this->drawing_field->y(),
                                     this->ui->statementsList->x(),
                                     this->height() - this->ui->UpperPanelFoneLabel->height() -
                                     this->ui->menubar->y());



    this->ui->UpperPanelFoneLabel->setGeometry(this->ui->UpperPanelFoneLabel->x(),
                                               this->ui->UpperPanelFoneLabel->y(),
                                               this->width(),
                                               this->ui->UpperPanelFoneLabel->height());
   // this->update();
}

void SimulatingForm::on_editModeCheckBox_stateChanged(int arg1)
{

}

void SimulatingForm::on_pauseButton_clicked(bool checked)
{

}

void SimulatingForm::on_editModeCheckBox_toggled(bool checked)
{
    if (this->simulator.isOnPause() && this->has_began_simulation)
        this->ui->editModeCheckBox->setChecked(false);
}
