#include "project.h"

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
{
    this->widget = widget;
    lcd = new Lcd(rows, cols, color, widget);

    addString("Predkosc"); //added this strings for tests
    addString("podzielnica");
    addString("stol");
    addString("kierunek");
}

Project::~Project()
{
    delete lcd;
}

void Project::addString(QString string)
{
    if(unPlacedBoxes.length() >= 1)
        unPlacedBoxes.push_back(new UnPlacedBox(this, widget, unPlacedBoxes.length(), string, QPoint(unPlacedBoxes.last()->geometry().x(), unPlacedBoxes.last()->geometry().y() + 50)));
    else
        unPlacedBoxes.push_back(new UnPlacedBox(this, widget, 0, string, QPoint(820, 100)));
}

bool Project::check(QPoint point)
{
    QPoint mappedPoint = lcd->mapFromParent(point);

    for(int i = 0; i < lcd->getNumberOfCells(); i++)
    {
        Cell* cell = lcd->getCell(i);

        //checks if the mouse during the drop is in coordinates of any cell (did the user drop on the cell or wherever)
        if((mappedPoint.x() >= cell->x()) && (mappedPoint.x() <= cell->x() + cell->width()))
        {
            if((mappedPoint.y() >= cell->y()) && (mappedPoint.y() <= cell->y() + cell->height()))
            {
                //checks if the cell is empty
                if(cell->getId() == -1)
                {
                    lcd->setDroppedCell(i);
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
        //check if its possible to drop this there (overfill cover)
        if(lcd->getDroppedCell() + string.length() <= lcd->getNumberOfCells())
        {
            for(int i = 0; i < string.length(); i++)
            {
                lcd->getCell(lcd->getDroppedCell() + i)->setText(string.at(i));
                lcd->getCell(lcd->getDroppedCell() + i)->setId(id);
            }
        }

        lcd->setDroppedCell(-1); //release the selected cell (reset) after operation confirmed
        return true;
    }

   return false;

}

