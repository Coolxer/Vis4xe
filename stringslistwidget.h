#ifndef STRINGSLISTWIDGET_H
#define STRINGSLISTWIDGET_H

#include <QWidget>

#include <QVector>

#include <unplacedbox.h>

#include <QtDebug>

class Project;

class StringsListWidget : public QWidget
{
private:
    QWidget* widget;
    Project* project;

    QVector <UnPlacedBox*> boxes;

public:
    StringsListWidget(){}
    StringsListWidget(Project* project, QWidget* widget);

    ~StringsListWidget();

    void addStringWidget(QString name);
    void deleteStringWidget(int id);
    void organize();
    void loadBoxesFromFile(QVector <UnPlacedBox*> boxes) { this->boxes = boxes; }

    int getAmount() { return boxes.length(); }

    UnPlacedBox* getBox(int i) { return boxes.at(i); }

};

#endif // STRINGSLISTWIDGET_H
