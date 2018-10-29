#include "project.h"

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
{
    this->widget = widget;
    lcd = new Lcd(rows, cols, color, widget);

    addString("elo");
    replaceBoxes();
}

Project::~Project()
{
    delete lcd;
}

void Project::replaceBoxes()
{
    for(int i = 0, j = 100; i < unPlacedBoxes.length(); i++, j+=50)
        unPlacedBoxes[i]->move(820, j);
}

void Project::addString(QString string)
{
    unPlacedStrings.push_back(string);
    unPlacedBoxes.push_back(new UnPlacedBox(this, widget, string));
}

bool Project::check(QPoint point)
{
    for(int i = 0; i < lcd->getCells().length(); i++)
    {
        if(point.x() >= lcd->getCells().at(i)->geometry().x() && point.x() <= lcd->getCells().at(i)->geometry().x() + lcd->getCells().at(i)->geometry().width())
            if(point.y() >= lcd->getCells().at(i)->geometry().y() && point.y() <= lcd->getCells().at(i)->geometry().y() + lcd->getCells().at(i)->geometry().height())
            {
                lcd->setCurrentCell(i);
                //break;
                return true;
            }
    }
    return false;
}

bool Project::writeOnLcd(QString string, QPoint point)
{
    if(check(point))
    {
        if(lcd->getCurrentCell() + string.length() <= lcd->getCells().length())
        {
            for(int i = 0; i < string.length(); i++)
            {
                lcd->getCells().at(lcd->getCurrentCell() + i)->setText(string.at(i));
            }
        }
        return true;
    }
    else
        return false;
}

