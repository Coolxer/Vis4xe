#include "project.h"

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
{
    this->widget = widget;
    lcd = new Lcd(rows, cols, color, widget);

    //addString("Predkosc"); //added this strings for tests
    //addString("podzielnica");


    /*
    listWidget = new QListWidget(widget);
    listWidget->setGeometry(810, 100, 142, 350);
    listWidget->setSpacing(5);
    */

    /*

    QListWidgetItem* item = new QListWidgetItem(listWidget);

    listWidget->addItem(item);

    listWidget->setItemWidget(item, unPlacedBoxes[0]);

    */

    /*
    listWidget->addItem(new QListWidgetItem(listWidget));
    listWidget->item(0)->setSizeHint(QSize(132, 50));
    listWidget->setItemWidget(listWidget->item(0), unPlacedBoxes[0]);
    */
}

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget, QVector <Cell*> cells, QVector <UnPlacedBox*> unPlacedBoxes)
{
    this->widget = widget;
    this->unPlacedBoxes = unPlacedBoxes;
    lcd = new Lcd(rows, cols, color, widget, cells);
}

Project::~Project()
{
    delete lcd;

    delete listWidget;
}

void Project::addString(QString string)
{
    if(unPlacedBoxes.length() >= 1)
        unPlacedBoxes.push_back(new UnPlacedBox(this, widget, unPlacedBoxes.length(), string, QPoint(unPlacedBoxes.last()->x(), unPlacedBoxes.last()->y() + 50)));
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

bool Project::writeOnLcd(UnPlacedBox* box)
{
    if(check(box->getLastPosition()))
    {
        //check if its possible to drop this there (overfill cover)
        if(lcd->getDroppedCell() + box->text().length() <= lcd->getNumberOfCells())
        {
            bool allCellsEnabled = true;

            for(int i = 0; i < box->text().length(); i++)
            {
                if(lcd->getCell(lcd->getDroppedCell() + i)->getId() != -1)
                {
                    allCellsEnabled = false;
                    break;
                }
            }

            if(allCellsEnabled)
            {
                for(int i = 0; i < box->text().length(); i++)
                {
                    lcd->getCell(lcd->getDroppedCell() + i)->setText(box->text().at(i));
                    lcd->getCell(lcd->getDroppedCell() + i)->setId(box->getId());
                    qDebug()<<lcd->getCell(lcd->getDroppedCell() + i)->getId();
                }

                organizeBoxes(box);
                lcd->setDroppedCell(-1); //release the selected cell (reset) after operation confirmed

                return true;
            }
        }
    }
   return false;
}

void Project::organizeBoxes(UnPlacedBox* box)
{

    QPoint boxStartPos = box->getStartPosition();

    for(int i = box->getId() + 1; i < unPlacedBoxes.length(); i++)
    {
        if(unPlacedBoxes[i]->x() != 0)
        {
            unPlacedBoxes[i]->move(unPlacedBoxes[i]->x(), unPlacedBoxes[i]->y() - 50);
        }
    }
}

void Project::prepareToSave()
{
    jsonObject["name"] = name;
    jsonObject["rows"] = lcd->getRowsAmount();
    jsonObject["cols"] = lcd->getColsAmount();
}


