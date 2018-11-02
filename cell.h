#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QColor>
#include <QString>
#include <QEvent>

#include <QApplication>

//#include "lcd.h"

class Lcd;

class Cell : public QLabel
{
private:
    Lcd* lcd;

    QColor color; // the color of the cell (inherited(got) from lcd)
    QString string; //the letter of the QLabel, normally its null = ""

    int id = -1;//this variable get you know if it is written to any string
                    //that means the the cell is empty // none string here

    int index; //this helps to get know on over the cell we are

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

    void mousePressEvent(QMouseEvent*);

public:
    Cell(){}
    Cell(Lcd* lcd, int index, QColor color);

    ~Cell();

    void setId(int id) { this->id = id; }
    int getId() { return this->id; }

};

#endif // CELL_H
