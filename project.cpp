#include "project.h"

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
{
    this->widget = widget;
    lcd = new Lcd(rows, cols, color, widget);

    addString("elo");
}

Project::~Project()
{
    delete lcd;
}

    //for(int i = 0, j = 100; i < unPlacedBoxes.length(); i++, j+=50)
    //   unPlacedBoxes[i]->move(820, j);

void Project::addString(QString string)
{
    unPlacedStrings.push_back(string);

    if(unPlacedBoxes.length() > 1)
        unPlacedBoxes.push_back(new UnPlacedBox(this, widget, string, QPoint(unPlacedBoxes.last()->geometry().x(), unPlacedBoxes.last()->geometry().y() + 50)));
    else
        unPlacedBoxes.push_back(new UnPlacedBox(this, widget, string, QPoint(820, 100)));
}

bool Project::check(QPoint point)
{
    for(int i = 0; i < lcd->getCells().length(); i++)
    {
        // check if the grabBox is over any cell
        if(point.x() >= lcd->getCells().at(i)->geometry().x() && point.x() <= lcd->getCells().at(i)->geometry().x() + lcd->getCells().at(i)->geometry().width())
        {
            if(point.y() >= lcd->getCells().at(i)->geometry().y() && point.y() <= lcd->getCells().at(i)->geometry().y() + lcd->getCells().at(i)->geometry().height())
            {
                //check if the cell does not have any letter  // is it free?
                if(lcd->getCells().at(i)->getId() == -1)
                {
                    lcd->setSelectedCell(i);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Project::writeOnLcd(QString string, QPoint point)
{
    if(check(point))
    {
        if(lcd->getSelectedCell() + string.length() <= lcd->getCells().length())
        {
            for(int i = 0; i < string.length(); i++)
            {
                lcd->getCells().at(lcd->getSelectedCell() + i)->setText(string.at(i));
            }
        }
        lcd->setSelectedCell(-1);
        return true;
    }
    else
        return false;
}

