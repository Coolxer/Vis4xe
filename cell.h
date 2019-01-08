#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QString>
#include <QEvent>

#include <QApplication>

class Lcd;

class Cell : public QLabel
{
private:
    Lcd* lcd; //the pointer to its parent

    QString string; //the letter of the QLabel, normally its null = ""

    int id = -1;//this variable get you know if it is written to any string (-1 mean "empty")

    int index; //the index of the cell in the lcd vector (from top-left = 0)

    void init();

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

    void mousePressEvent(QMouseEvent*);

public:
    Cell(){}
    Cell(Lcd* lcd, int index);
    Cell(Lcd* lcd, int index, int id, QString value);

    ~Cell();

    void setId(int id) { this->id = id; }
    int getId() { return id; }

    QString getValue() { return text(); }

};

#endif // CELL_H
