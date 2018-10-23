#ifndef LCD_H
#define LCD_H

#include <QLabel>
#include <QColor>

#include <QWidget>

#include <QVector>

class Lcd
{
private:
    unsigned short rows;
    unsigned short cols;
    QColor color;

    unsigned short numberOfCells;

    QWidget* widget;

    QVector <QLabel*> cells;

    void initCells();

public:
    Lcd(){};
    Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Lcd();
};

#endif // LCD_H
