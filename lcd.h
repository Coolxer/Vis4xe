#ifndef LCD_H
#define LCD_H

#include <QColor>
#include <QWidget>
#include <QVector>

#include <QDebug>

#include "mylabel.h"

class Lcd
{
private:
    unsigned short rows;
    unsigned short cols;
    QColor color;

    QWidget* widget;

    QVector <MyLabel*> cells;

    unsigned short numberOfCells;

    void initCells();

public:
    Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Lcd();

    QVector <MyLabel*> getCells() { return cells; };
};

#endif // LCD_H
