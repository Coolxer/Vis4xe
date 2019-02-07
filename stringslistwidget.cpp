#include "stringslistwidget.h"

StringsListWidget::StringsListWidget(Project* project)
{
    this->project = project;

    size = 0;
}

StringsListWidget::~StringsListWidget()
{
    for(int i = 0; i < boxes.length(); i++)
    {
        boxes[i]->setVisible(false);
        boxes.removeAt(i);
    }
}

void StringsListWidget::addStringWidget(QString name)
{
    if(size < 10)
    {
        if(boxes.length() > 0)
            boxes.push_back(new UnPlacedBox(project, size, name, QPoint(810, boxes.last()->y() + 40)));
        else
            boxes.push_back(new UnPlacedBox(project, 0, name, QPoint(810, 10)));

        size++;
    }

    boxes.last()->show(true);
}

void StringsListWidget::deleteStringWidget(int index)
{
    if(index != size - 1)
        for(int i = index + 1; i < size; i++)
            boxes[i]->decrease();

    delete boxes[index];
    boxes.removeAt(index);
    //boxes.erase(boxes.begin() + index);

    size--;

    if(size > 0)
        organize(index);
}

void StringsListWidget::organize(int index)
{
    if(index == 0)
    {
        boxes[0]->moveTo(QPoint(810, 10));
        index++;
    }

    for(int i = index; i < size; i++)
        boxes[i]->moveTo(QPoint(810, boxes[i-1]->y() + 40));
}

