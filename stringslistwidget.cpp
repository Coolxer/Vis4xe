#include "stringslistwidget.h"

StringsListWidget::StringsListWidget(Project* project, QWidget* widget): QWidget(widget)
{
    this->project = project;

    setGeometry(806, 5, 150, 360);
    setStyleSheet("QWidget{ background-color: green; }");

}

StringsListWidget::~StringsListWidget()
{

}

void StringsListWidget::addStringWidget(QString name)
{
    if(boxes.length() > 0)
        boxes.push_back(new UnPlacedBox(project, this, boxes.length(), name, QPoint(5, boxes.last()->y() + 40)));
    else
        boxes.push_back(new UnPlacedBox(project, this, 0, name, QPoint(5, 5)));

    boxes.last()->show();
}

void StringsListWidget::deleteStringWidget(int id)
{
    boxes.removeAt(id);
}

void StringsListWidget::organize()
{

}
