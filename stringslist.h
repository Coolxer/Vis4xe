#ifndef STRINGSLIST_H
#define STRINGSLIST_H

#include <QWidget>
#include <QVector>

#include "unplacedbox.h"

class Project;

class StringsList
{
private:
    Project* project; //the pointer to the project object to which the class belongs

    QVector <UnPlacedBox*> boxes; //the vector<> of the strings boxes

    int counter; // the counter of the total unplacedBoxes created (not decreasing after deleting) for id of new box

    void organize(int index); //organizes the unplacedBoxes after one of them was removed or dragged out    

public:
    StringsList(){}
    StringsList(Project* project);
    ~StringsList();

    int getAmount() { return boxes.length(); }
    UnPlacedBox* getBox(int i) { return boxes.at(i); }

    void addString(QString name);//adds new string to the vector
    void deleteString(int index); //deletes the selected string
    void loadBoxesFromFile(QVector <UnPlacedBox*> boxes) { this->boxes = boxes; counter = boxes.last()->getId() + 1; } //the function that loads the unPlacedBoxes from file


};

#endif // STRINGSLIST_H
