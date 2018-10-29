#ifndef LCD_H
#define LCD_H

#include <QColor>
#include <QWidget>
#include <QVector>

#include <QDebug>

#include "Cell.h"

#include <QMouseEvent>

#include <QGridLayout>

#include <QPoint>


class Lcd : public QWidget
{
private:
    unsigned short rows;
    unsigned short cols;
    QColor color;

    QWidget* widget;

    QVector <Cell*> cells;

    unsigned short numberOfCells;

    void initCells();

    int selectedCell;

    QGridLayout* layout;

protected:
    void mousePressEvent(QMouseEvent* event);
public:
    Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Lcd();

    QVector <Cell*> getCells() { return cells; };

    void setSelectedCell(int i) { selectedCell = i; };
    int getSelectedCell() { return selectedCell; };

};

#endif // LCD_H
