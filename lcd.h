#ifndef LCD_H
#define LCD_H

#include <QColor>
#include <QWidget>
#include <QVector>

#include <QDebug>

#include "cell.h"

#include <QMouseEvent>

#include <QGridLayout>

#include <QPoint>

#include <QKeyEvent>


class Lcd : public QWidget
{
private:
    unsigned short rows; //number of lcd rows
    unsigned short cols; //number of lcd cols
    QColor color; //color of the scren ( cells color)

    QWidget* widget; //the pointer to main widget which on the lcd is drawing

    int numberOfCells = 0; //the helping variable to storing number of cells ( rows * cols)

    void initCells();  //this function creates cells and sets their options, then appends its to vector

    int selectedCell = -1; //the index of the cell which on the user dropped the UnplacedBox string, normally is -1

    int hoveredCell = -1; //the index of the cell which on the mouse is over, normally -1

    int droppedCell = -1; //the index of the cell which on the user dropped the UnplacedBox string

    bool editMode = false; //the status of the Edit string mode // edit mode allows to changing the position
                           // of the string that is already placed in lcd or remove it

    QString selectedString; //the string on the lcd which is focused and just opened edit mode

    QVector <int> selectedNumbersOfCells; //the vector that is keeping the the cells number that are together connected
                                //with one id // using for edit mode

    QVector <Cell*> cells;

    void cancelEditMode();

protected:
    //void mousePressEvent(QMouseEvent* event);
    //void mouseMoveEvent(QMouseEvent* event) override; //inside this event the cells are changing colors in the
                                                      //face of cursor and the string that they are written to
    void keyPressEvent(QKeyEvent* event);

public:
    Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget, QVector <Cell*> cells);
    ~Lcd();

    //QVector <Cell*> getCells() { return cells; }; //getter that allows to read cells

    //for editing mode
    void setSelectedCell(int m);
    int getSelectedCell() { return selectedCell; }

    //for just appereance ? and info the user
    void setHoveredCell(int m);
    int getHoveredCell() { return hoveredCell; }

    //for drag & drop unplacebox
    void setDroppedCell(int m) { droppedCell = m; }
    int getDroppedCell() { return droppedCell; }

    Cell* getCell(int i) { return cells[i]; }

    int getNumberOfCells() { return numberOfCells; }

    int getRowsAmount() { return rows; }
    int getColsAmount() { return cols; }
};

#endif // LCD_H
