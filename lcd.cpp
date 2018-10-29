#include "lcd.h"

Lcd::Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
{
    this->rows = rows;
    this->cols = cols;
    this->color = color;

    this->widget = widget;

    /* *********** */

    //for not typing in all the time during tests and developing
    this->rows = 4;
    this->cols = 20;

    /* ************* */

    numberOfCells = rows * cols;

    initCells();
}

Lcd::~Lcd()
{
    delete widget;
}

void Lcd::initCells()
{
    unsigned short m = 0 ;

    for(unsigned short i = 0; i < rows; i++)
    {
        for(unsigned short j = 0; j < cols; j++)
        {
            cells.push_back(new Cell(widget, QColor(255, 255, 255, 0)));

            cells[m]->setGeometry(QRect(0, 0, 20, 30));
            cells[m]->setStyleSheet("QLabel { background-color: #0099ff; color: #FFFFFF; font-size: 25px; }");
            cells[m]->setAlignment(Qt::AlignCenter);

            cells[m]->move(150 + (25 * j), 200 + (i * 35));
            m++;
        }
    }



}

