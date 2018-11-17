#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QColor>
#include <QString>
#include <QEvent>

#include <QApplication>

class Lcd;

class Cell : public QLabel
{
private:
    Lcd* lcd; //the pointer to its parent

    QColor color; // the color of the cell (inherited(got) from lcd)
    QString string; //the letter of the QLabel, normally its null = ""

    int id = -1;//this variable get you know if it is written to any string (-1 mean "empty")

    int index; //the index of the cell in the lcd vector (from top-left = 0)

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

    void mousePressEvent(QMouseEvent*);

public:
    Cell(){}
    Cell(Lcd* lcd, int index, QColor color);
    Cell(Lcd* lcd, int index, QColor color, int id);

    ~Cell();

    void setId(int id) { this->id = id; }
    int getId() { return id; }

};

#endif // CELL_H
