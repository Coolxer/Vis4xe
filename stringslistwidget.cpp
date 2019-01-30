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
    if(boxes.length() > 0)
        boxes.push_back(new UnPlacedBox(project, boxes.length(), name, QPoint(810, boxes.last()->y() + 40)));
    else
        boxes.push_back(new UnPlacedBox(project, 0, name, QPoint(810, 5)));

    boxes.last()->show(true);
}

void StringsListWidget::deleteStringWidget(int id)
{
    delete boxes.at(id);
    boxes.removeAt(id);
}

void StringsListWidget::organize()
{

}
