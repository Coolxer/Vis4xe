#ifndef LCD_H
#define LCD_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QVector>

#include "cell.h"

class Project;

class Lcd : public QWidget
{
private:
    Project* project;  //the pointer to the project that lcd belongs to

    int rows; //number of lcd rows
    int cols; //number of lcd cols
    int numberOfCells; //rows * cols

    QVector <Cell*> cells; //the vector of the lcd's cells

    int currentId = -1; //the id of the current selected cell
    Cell* selectedCell = nullptr; //the pointer to the selected cell
    Cell* droppedCell = nullptr; //the pointer to the dropped on cell

    bool editMode = false; //the status of the Edit string mode // edit mode allows to changing the position
                           // of the string that is already placed in lcd or remove it

    /* Poles using in edit Mode */
    QString selectedString; //the string on the lcd which is focused and just opened edit mode

    QVector <int> selectedNumbersOfCells; //the vector of the numbers of cells that would be using in editMode, keeping for restore settings

    QVector <int> operationCells; //the vector of the number of cells which on the operations are provided

    void initCells();  //this function creates cells and sets their options, then appends its to vector

    void organize(); //the function that is organized the cells loaded from file

    void cancelChanges(); //cancels the changes in editMode and exit (DELETE KEY)
    void unpin(); //this function unpins the string from the lcd
    void exitEditMode(); //accepts the changes in editMode and exit (ENTER KEY)

    void keyPressEvent(QKeyEvent* event);

public:
    Lcd(){}
    Lcd(int rows, int cols, Project* project);
    ~Lcd(){}

    void setSelectedCell(int index); //marks the cell as selected
    void setDroppedCell(int index) { (index == -1) ? droppedCell = nullptr : droppedCell = cells[index];}
    void loadCellsFromFile(QVector<Cell*> cells); //using for append the Array of cells loaded from *.json file

    Cell* getCell(int i) { return cells[i]; }
    Cell* getDroppedCell() { return droppedCell; }
    Cell* getSelectedCell() { return selectedCell; }

    int getNumberOfCells() { return numberOfCells; }
    int getRows(){ return rows; }
    int getCols(){ return cols; }
    bool editEnabled() { return editMode; }
};

#endif // LCD_H
