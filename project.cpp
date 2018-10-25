#include "project.h"

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
{
    lcd = new Lcd(rows, cols, color, widget);
    stringsList = new StringsList(widget, lcd->getCells());
}

Project::~Project()
{
    delete lcd;
    delete stringsList;
}

