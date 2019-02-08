#include "stringslist.h"

StringsList::StringsList(Project* project)
{
    this->project = project;

    counter = 0;
}

StringsList::~StringsList()
{
    for(int i = 0; i < boxes.length(); i++)
    {
        boxes[i]->setVisible(false);
        boxes.removeAt(i);
    }
}

void StringsList::organize(int index)
{
    if(index == 0)
    {
        boxes[0]->moveTo(QPoint(810, 10));
        index++;
    }

    for(int i = index; i < boxes.length(); i++)
        boxes[i]->moveTo(QPoint(810, boxes[i-1]->y() + 40));
}

void StringsList::addString(QString name)
{
    if(boxes.length() < 10)
    {
        if(boxes.length() > 0)
            boxes.push_back(new UnPlacedBox(project, boxes.length(), counter, name, QPoint(810, boxes.last()->y() + 40)));
        else
            boxes.push_back(new UnPlacedBox(project, 0, counter, name, QPoint(810, 10)));

        counter++;
    }

    boxes.last()->show(true);
}

void StringsList::deleteString(int index)
{
    if(index != boxes.length() - 1)
        for(int i = index + 1; i < boxes.length(); i++)
            boxes[i]->decrease();

    delete boxes[index];
    boxes.removeAt(index);

    if(boxes.length() > 0)
        organize(index);
}



