#include "lcd.h"

Lcd::Lcd(unsigned short rows, unsigned short cols, QColor color)
{
    this->rows = rows;
    this->cols = cols;
    this->color = color;
}
