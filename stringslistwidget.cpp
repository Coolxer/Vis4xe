#include "stringslistwidget.h"

StringsListWidget::StringsListWidget(Project* project)
{
    this->project = project;
}

StringsListWidget::~StringsListWidget()
{
    for(int i = 0; i < boxes.length(); i++)
    {
        boxes.at(i)->setVisible(false);
        boxes.removeAt(i);
    }
}

void StringsListWidget::addStringWidget(QString name)
{
    if(boxes.length() < 10)
    {
        if(boxes.length() > 0)
            boxes.push_back(new UnPlacedBox(project, boxes.length(), name, QPoint(810, boxes.last()->y() + 40)));
        else
            boxes.push_back(new UnPlacedBox(project, 0, name, QPoint(810, 10)));
    }

    boxes.last()->show(true);
}

void StringsListWidget::deleteStringWidget(int id)
{
    if(id != boxes.length() - 1)
        for(int i = id + 1; i < boxes.length(); i++)
            boxes[i]->decrease();

    delete boxes[id];
    //boxes.removeAt(id);
    boxes.erase(boxes.begin() + id);

    if(boxes.length() > 0)
        organize(id);
}

void StringsListWidget::organize(int id)
{
    if(id == 0)
    {
        boxes[0]->moveTo(QPoint(810, 10));
        id++;
    }

    for(int i = id; i < boxes.length(); i++)
        boxes[i]->moveTo(QPoint(810, boxes[i-1]->y() + 40));
}

