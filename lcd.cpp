#include "lcd.h"

Lcd::Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
{
    this->rows = rows;
    this->cols = cols;
    this->color = color;

    this->widget = widget;

    initCells();

    //QPushButton* button = new QPushButton("elo", widget);
    //button->show();
}

Lcd::~Lcd()
{
    //delete cells;
    delete widget;
}

void Lcd::initCells()
{
    numberOfCells = rows * cols;

    int m = 0 ;

    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            cells.push_back(new MyLabel(widget, QColor(255, 255, 255, 0)));

            cells[m]->setGeometry(QRect(0, 0, 20, 30));
            cells[m]->setStyleSheet("QLabel { background-color: #0099ff; color: #FFFFFF; font-size: 25px;}");
            cells[m]->setAlignment(Qt::AlignCenter);

            cells[m]->move(50 + (25 * i), 200 + (j * 35));
            cells[m]->show();
            m++;
        }
    }

    cells[25]->setText("H");

}

