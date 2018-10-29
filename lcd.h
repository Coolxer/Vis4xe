#ifndef LCD_H
#define LCD_H

#include <QColor>
#include <QWidget>
#include <QVector>

#include <QDebug>

#include "mylabel.h"

#include <QMouseEvent>

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

    int currentCell = -1;

public:
    Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Lcd();

    QVector <MyLabel*> getCells() { return cells; };

    void setCurrentCell(int i) { currentCell = i; }; //set the cell which on is dropped the unplacedBox
    int getCurrentCell() { return currentCell; }; //return the number of current dropped cell // if is none the function return -1
};

#endif // LCD_H
