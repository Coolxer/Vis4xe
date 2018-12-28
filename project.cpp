#include "project.h"

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
{
    this->name = name;

    projectNameBox = new QLabel(widget);

    container = new QWidget(widget);

    container->setGeometry(0, 60, 960, 400);

    lcd = new Lcd(rows, cols, color, container);

    stringsWidget = new StringsListWidget(this);

    projectNameBox->setGeometry(480, 3, 120, 54);
    projectNameBox->setStyleSheet("QLabel{ font-family: Vladimir Script; font-size: 32px; color: #FF0000; }");
    projectNameBox->setText(name);
    projectNameBox->setAlignment(Qt::AlignCenter);
    projectNameBox->show();
}

Project::~Project()
{
    projectNameBox->setVisible(false);
    delete projectNameBox;

    lcd->setVisible(false);
    delete lcd;

    delete stringsWidget;

    container->setVisible(false);
    delete container;
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
    if(check(box->getDragBoxPoint()))
    {
        //get the row we are currently in
        int whichRow = lcd->getDroppedCell() / lcd->getCols();

        whichRow++;

        //check if its possible to drop this there (overfill cover)
        //if(lcd->getDroppedCell() + box->text().length() <= lcd->getNumberOfCells())
        //checks if the lcd overfill
        if(lcd->getDroppedCell() < whichRow * lcd->getCols())
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
                }

                lcd->setDroppedCell(-1); //release the selected cell (reset) after operation confirm

                return true;
            }
        }
    }
   return false;
}


void Project::loadUnplacedBoxes(QVector<UnPlacedBox*> unPlacedBoxes)
{
    stringsWidget->loadBoxesFromFile(unPlacedBoxes);
}

void Project::loadCells(QVector<Cell*> cells)
{
    lcd->loadCellsFromFile(cells);
}


