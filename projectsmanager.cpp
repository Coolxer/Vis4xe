#include "projectsmanager.h"

#include <QStackedWidget>

#include "projectnamebox.h"
#include "cell.h"
#include "unplacedbox.h"

ProjectsManager::ProjectsManager(QWidget* homePage, QWidget* editPage, QStackedWidget* stackedWidget, QStackedWidget* prList)
{
    this->homePage = homePage;
    this->editPage = editPage;
    this->stackedWidget = stackedWidget;
    this->prList = prList;

    fileManager = new FileManager();

    readBoxes();
}

ProjectsManager::~ProjectsManager()
{
    delete currentProject;
    delete fileManager;
}

void ProjectsManager::readBoxes()
{
    boxes.clear();

    QByteArray data = fileManager->shortRead();

    if(data != nullptr)
    {
        QJsonDocument doc = QJsonDocument::fromJson(data);

        boxesArray = doc.object()["projects"].toArray();

        if(boxesArray.size() > 0 )
        {
            int r = boxesArray.size() / 3;

            if(boxesArray.size() % 3 != 0)
                r++;

            int lastItemColumn = boxesArray.size() % 3;

            if(lastItemColumn == 0)
                lastItemColumn = 3;

            if(r == 1)
            {
                if(lastItemColumn == 1)
                    lastItemColumn = 2;
                else if (lastItemColumn == 2)
                    lastItemColumn = 1;
            }

            int c = 3;

            if(boxesArray.size() < c)
                c = lastItemColumn;

            int m = 0;

            for(int i = 0; i < r; i++)
            {
                if(i == r-1)
                    c = lastItemColumn;

                for(int j = 0; j < c; j++)
                {
                    boxes.push_back(new ProjectNameBox(homePage, boxesArray[m].toObject().value("name").toString(), boxesArray[m].toObject().value("path").toString(), QPoint(120 + (260 *j), (120 * i) + 100)));
                    boxes[m]->init(this);

                    m++;
                }
            }
            prList->setCurrentIndex(0);
        }
        else
            prList->setCurrentIndex(1);

    }
}

void ProjectsManager::loadProject(ProjectNameBox* box, QString path)
{
    QByteArray data = fileManager->readProject(path);

    if(data != nullptr)
    {
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();

        QJsonValue name = obj.value("name");
        QJsonValue rows = obj.value("rows");
        QJsonValue cols = obj.value("cols");
        QJsonValue color = obj.value("color");

        QJsonArray cellsArray = obj.value("cells").toArray();
        QJsonArray unplacedBoxesArray = obj.value("unPlacedBoxes").toArray();

        QVector <Cell*> cells;
        QVector <UnPlacedBox*> unPlacedBoxes;

        currentProject = new Project(name.toString(), rows.toInt(), cols.toInt(), editPage);

        for(int i = 0; i < cellsArray.size(); i++)
            cells.push_back(new Cell(currentProject->getLcd(), i, cellsArray[i].toObject().value("id").toInt(), cellsArray[i].toObject().value("value").toString()));

        for(int i = 0; i < unplacedBoxesArray.size(); i++)
        {
            if(i > 0)
                unPlacedBoxes.push_back(new UnPlacedBox(currentProject, unplacedBoxesArray[i].toObject().value("id").toInt(), unplacedBoxesArray[i].toObject().value("value").toString(), QPoint(810, unPlacedBoxes.last()->y() + 40)));
            else
                unPlacedBoxes.push_back(new UnPlacedBox(currentProject, unplacedBoxesArray[i].toObject().value("id").toInt(), unplacedBoxesArray[i].toObject().value("value").toString(), QPoint(810, 5)));
        }

        currentProject->loadCells(cells);
        currentProject->loadUnplacedBoxes(unPlacedBoxes);

        stackedWidget->setCurrentIndex(2);
    }
    else
    {
        box->hide();
        delete box;
    }

}

void ProjectsManager::createProject(QString name, unsigned short rows, unsigned short cols)
{
    currentProject = new Project(name, rows, cols, editPage);
}

void ProjectsManager::saveProject()
{
    QJsonDocument doc;

    QJsonObject obj;

    QJsonArray cells;
    QJsonArray unPlacedBoxes;

    QString idStr("id");
    QString valueStr("value");

    for(int i = 0; i < currentProject->getLcd()->getNumberOfCells(); i++)
    {
        QJsonObject cell;
        cell.insert(idStr, QJsonValue(currentProject->getLcd()->getCell(i)->getId()));
        cell.insert(valueStr, QJsonValue(currentProject->getLcd()->getCell(i)->getValue()));

        cells.push_back(QJsonValue(cell));
    }

    for(int i = 0; i < currentProject->getStringsWidget()->getAmount(); i++)
    {
        QJsonObject unPlacedBox;
        unPlacedBox.insert(idStr, QJsonValue(currentProject->getStringsWidget()->getBox(i)->getId()));
        unPlacedBox.insert(valueStr, QJsonValue(currentProject->getStringsWidget()->getBox(i)->getValue()));

        unPlacedBoxes.push_back(QJsonValue(unPlacedBox));
    }

    obj.insert(QString("name"), QJsonValue(currentProject->getName()));
    obj.insert(QString("rows"), QJsonValue(currentProject->getLcd()->getRows()));
    obj.insert(QString("cols"), QJsonValue(currentProject->getLcd()->getCols()));

    obj.insert(QString("cells"), QJsonValue(cells));
    obj.insert(QString("unPlacedBoxes"), QJsonValue(unPlacedBoxes));

    doc.setObject(obj);

    QString fileName = QFileDialog::getSaveFileName(editPage, "Open File",
                                                   currentProject->getName(),
                                                    "Json (*.json);;All Files (*)");

    QJsonDocument doc2;
    QJsonObject obj2;
    QJsonObject item;

    item.insert(QString("name"), QJsonValue(currentProject->getName()));
    item.insert(QString("path"), QJsonValue(fileName));

    boxesArray.push_back(item);

    obj2.insert(QString("projects"), boxesArray);

    doc2.setObject(obj2);

    fileManager->saveProject(doc, doc2, fileName);

    readBoxes();

}

