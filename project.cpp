#include "project.h"

#include <QPushButton>

Project::Project(QString name, unsigned short rows, unsigned short cols, QWidget* widget, QPushButton* btn)
{
    this->name = name;

    projectNameBox = new QLabel(widget);
    container = new QWidget(widget);

    container->setGeometry(0, 60, 960, 400);

    lcd = new Lcd(rows, cols, this);
    stringsList = new StringsList(this);

    sBtn = btn;

    projectNameBox->setGeometry(480, 3, 120, 54);
    projectNameBox->setStyleSheet("QLabel{ font-family: Bradley Hand ITC; font-size: 32px; color: #FF0000; }");
    projectNameBox->setText(name);
    projectNameBox->setAlignment(Qt::AlignCenter);
    projectNameBox->show();

    setSaved(false);
}

Project::~Project()
{
    projectNameBox->setVisible(false);
    delete projectNameBox;

    lcd->setVisible(false);
    delete lcd;

    delete stringsList;

    container->setVisible(false);
    delete container;
}

bool Project::check(QPoint point)
{
    QPoint mappedPoint = lcd->mapFromParent(point);

    Cell* cell;

    for(int i = 0; i < lcd->getNumberOfCells(); i++)
    {
        cell = lcd->getCell(i);

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
        //check if its possible to drop this there (overfill cover)
        if(lcd->getDroppedCell()->getIndex() + box->text().length() <= lcd->getDroppedCell()->getRow()* lcd->getCols())
        {
            bool allCellsEnabled = true;

            for(int i = 0; i < box->text().length(); i++)
            {
                if(lcd->getCell(lcd->getDroppedCell()->getIndex() + i)->getId() != -1)
                {
                    allCellsEnabled = false;
                    break;
                }
            }

            if(allCellsEnabled)
            {
                for(int i = 0; i < box->text().length(); i++)
                {
                    lcd->getCell(lcd->getDroppedCell()->getIndex() + i)->setText(box->text().at(i));
                    lcd->getCell(lcd->getDroppedCell()->getIndex() + i)->setId(box->getId());
                }

                lcd->setDroppedCell(-1); //release the selected cell (reset) after operation confirm

                stringsList->deleteString(box->getIndex());

                setSaved(false);

                return true;
            }
        }
    }

   return false;
}

void Project::setPath(QString path)
{
    dirPath.clear();
    visPath.clear();
    avrPath.clear();

    if(path.isEmpty())
        return;

    if(!QFileInfo::exists(path))
    {
        for(int i = 0; i <= path.length() - 6; i++)
            dirPath += path[i];

        int x = 0;

        //visPath
        for(int i = path.length() -1; i >= 0; i--)
        {
            if(path[i] == '/')
                break;

            x++;
        }

        int k = path.length() - 1 - x;

        for(int i = k; i <= path.length()-1; i++)
            visPath += path[i];

        visPath = dirPath + visPath;

        //avrPath
        for(int i = 0; i <= visPath.length() - 1; i++)
        {
            if(visPath[i] == '.')
                break;

            avrPath += visPath[i];
        }

        avrPath += ".txt";
    }
    else
    {
        visPath = path;

        for(int i = 0; i <= visPath.length() - 1; i++)
        {
            if(visPath[i] == '.')
                break;

            avrPath += visPath[i];
        }

        avrPath += ".txt";
    }
}

void Project::setSaved(bool x)
{
    sBtn->setEnabled(!x);

    if(!x)
        sBtn->setStyleSheet("QPushButton{border: 2px solid #00cc00; color: #00cc00; border-radius:30; font-size: 20px;} QPushButton:hover{background-color: #00cc00; color: #333333;}");
    else
        sBtn->setStyleSheet("QPushButton{border: 2px solid #808080; color: #808080; border-radius:30; font-size: 20px; opacity: 0.5; }");
}


