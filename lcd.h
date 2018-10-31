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

#include "editmode.h"

#include <QKeyEvent>


class Lcd : public QWidget
{
private:
    unsigned short rows; //number of lcd rows
    unsigned short cols; //number of lcd cols
    QColor color; //color of the scren ( cells color)

    QWidget* widget; //the pointer to main widget which on the lcd is drawing

    QVector <Cell*> cells; //the vector of the cells (dynamic array)

    unsigned short numberOfCells; //the helping variable to storing number of cells ( rows * cols)

    void initCells();  //this function creates cells and sets their options, then appends its to vector

    int selectedCell; //the index of the cell which on the user dropped the UnplacedBox string, normally is -1

    QGridLayout* layout; //the layout to cleany keeping the cells in rows and cols

    bool editMode = false; //the status of the Edit string mode // edit mode allows to changing the position
                           // of the string that is already placed in lcd or remove it

    QString currentString; //the string on the lcd which is focused and just opened edit mode

    QVector <int> cellsNumbers; //the vector that is keeping the the cells number that are together connected
                                //with one id // using for edit mode

protected:
    void mousePressEvent(QMouseEvent* event);
    //void mouseMoveEvent(QMouseEvent* event) override; //inside this event the cells are changing colors in the
                                                      //face of cursor and the string that they are written to
    void keyPressEvent(QKeyEvent* event);

public:
    Lcd(unsigned short rows, unsigned short cols, QColor color, QWidget* widget);
    ~Lcd();

    QVector <Cell*> getCells() { return cells; }; //getter that allows to read cells

    void setSelectedCell(int i) { selectedCell = i; }; //setter the selectedCell
    int getSelectedCell() { return selectedCell; }; //getter the selectedCell

};

#endif // LCD_H
