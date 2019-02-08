#ifndef CELL_H
#define CELL_H

#include <QApplication>
#include <QLabel>

class Lcd;

class Cell : public QLabel
{
private:
    Lcd* lcd; //the pointer to its parent

    int id = -1;//this variable get you know if it is written to any string (-1 mean "empty")

    int index; //the index of the cell in the lcd vector (from top-left = 0)
    int row; //the row in which the cell is placed
    int col; //the column in which the cell is placed

    void init(); //prepares the array of cell in lcd

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

    void mousePressEvent(QMouseEvent*);

public:
    Cell(){}
    Cell(Lcd* lcd, int index);
    Cell(Lcd* lcd, int index, int id, QString value);

    void setId(int id) { this->id = id; }

    int getId() { return id; }
    int getRow(){ return row; }
    int getCol(){ return col; }
    int getIndex() { return index; }

};

#endif // CELL_H
