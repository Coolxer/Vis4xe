#ifndef LCD_H
#define LCD_H

#include <QColor>

#include <QWidget>
//#include <QLabel>

#include <QVector>

#include "mylabel.h"

class Lcd
{
private:
    unsigned short rows;
    unsigned short cols;
    QColor color;

    unsigned short numberOfCells;

    QWidget* widget;

    QVector <MyLabel*> cells;

    void initCells();

public:
    Lcd(){};
    Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Lcd();
};

#endif // LCD_H
