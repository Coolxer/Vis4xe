#include "project.h"

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
{
    this->widget = widget;
    lcd = new Lcd(rows, cols, color, widget);

    addString("Predkosc"); //added for test
    addString("podzielnica");
}

Project::~Project()
{
    delete lcd;
}

void Project::addString(QString string)
{
    //unPlacedStrings.push_back(string);

    if(unPlacedBoxes.length() >= 1)
        unPlacedBoxes.push_back(new UnPlacedBox(this, widget, unPlacedBoxes.length(), string, QPoint(unPlacedBoxes.last()->geometry().x(), unPlacedBoxes.last()->geometry().y() + 50)));
    else
        unPlacedBoxes.push_back(new UnPlacedBox(this, widget, 0, string, QPoint(820, 100)));
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

bool Project::writeOnLcd(QString string, QPoint point, int id)
{
    if(check(point))
    {
        if(lcd->getSelectedCell() + string.length() <= lcd->getCells().length())
        {
            for(int i = 0; i < string.length(); i++)
            {
                lcd->getCells().at(lcd->getSelectedCell() + i)->setText(string.at(i));
                lcd->getCells().at(lcd->getSelectedCell() + i)->setId(id);
            }
        }
        lcd->setSelectedCell(-1); //release the selected cell (reset) after operation confirmed
        return true;
    }
   return false;
}

