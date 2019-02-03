#ifndef LCD_H
#define LCD_H

#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QVector>
#include <QWidget>


#include "cell.h"

class Project;
class UnPlacedBox;

class Lcd : public QWidget
{
private:
    unsigned short rows; //number of lcd rows
    unsigned short cols; //number of lcd cols

    int numberOfCells;; //rows * cols

    void initCells();  //this function creates cells and sets their options, then appends its to vector

    void organize();

    int selectedCell = -1; //the index of the cell which on the user dropped the UnplacedBox string, normally is -1

    int currentId = -1;

    int hoveredCell = -1; //the index of the cell which on the mouse is over, normally -1

    int droppedCell = -1; //the index of the cell which on the user dropped the UnplacedBox string

    bool editMode = false; //the status of the Edit string mode // edit mode allows to changing the position
                           // of the string that is already placed in lcd or remove it

    QString selectedString; //the string on the lcd which is focused and just opened edit mode

    QVector <int> selectedNumbersOfCells; //the vector that is keeping the the cells number that are together connected
                                //with one id // using for edit mode

    QVector <int> operationCells;

    QVector <Cell*> cells;

    Project* project;
    UnPlacedBox* uBox;

    void cancelChanges();
    void acceptChanges();

    void exitEditMode();

    void keyPressEvent(QKeyEvent* event);

    void unpin();

public:
    Lcd(){}
    Lcd(unsigned short rows, unsigned short cols, QWidget* widget, Project* project);
    //Lcd(unsigned short rows, unsigned short cols, QWidget* widget, QVector <Cell*> cells);
    ~Lcd(){}

    //QVector <Cell*> getCells() { return cells; }; //getter that allows to read cells

    //for editing mode
    void setSelectedCell(int m);
    int getSelectedCell() { return selectedCell; }

    //for drag & drop unplacebox
    void setDroppedCell(int m) { droppedCell = m; }
    int getDroppedCell() { return droppedCell; }

    Cell* getCell(int i) { return cells[i]; }

    int getNumberOfCells() { return numberOfCells; }

    int getRows(){ return rows; }
    int getCols(){ return cols; }

    void appendCells(QVector<Cell*> cells) { this->cells = cells; }

    void loadCellsFromFile(QVector<Cell*> cells);

    bool editEnabled() { return editMode; };
};

#endif // LCD_H
