#ifndef STRINGSLISTWIDGET_H
#define STRINGSLISTWIDGET_H

#include <QWidget>

#include <QVector>

#include <unplacedbox.h>

#include <QtDebug>

class Project;

class StringsListWidget
{
private:
    Project* project; //the pointer to the project object to which the class belongs

    QVector <UnPlacedBox*> boxes; //the vector<> of the strings boxes

public:
    StringsListWidget(){}
    StringsListWidget(Project* project);

    ~StringsListWidget();

    void addStringWidget(QString name);//adds new string to the vector
    void deleteStringWidget(int id); //deletes the selected string
    void loadBoxesFromFile(QVector <UnPlacedBox*> boxes) { this->boxes = boxes; } //the function that loads the unPlacedBoxes from file

    int getAmount() { return boxes.length(); }

    UnPlacedBox* getBox(int i) { return boxes.at(i); }

};

#endif // STRINGSLISTWIDGET_H
