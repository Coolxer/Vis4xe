#include "projectsmanager.h"

#include <QStackedWidget>

#include "projectnamebox.h"
#include "cell.h"
#include "unplacedbox.h"

ProjectsManager::ProjectsManager(QWidget* homePage, QWidget* editPage, QStackedWidget* stackedWidget)
{
    this->homePage = homePage;
    this->editPage = editPage;
    this->stackedWidget = stackedWidget;

    fileManager = new FileManager(editPage);

    QByteArray data = fileManager->shortRead();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.object()["projects"].toArray();

    for(int i = 0; i < array.size(); i++)
    {
        boxes.push_back(new ProjectNameBox(homePage, array[i].toObject().value("name").toString(), array[i].toObject().value("path").toString(), QPoint(20 + (220) *i, 100)));
        boxes[i]->init(this);
    }
}

ProjectsManager::~ProjectsManager()
{
    delete homePage;
    delete editPage;
    delete stackedWidget;

    delete currentProject;
    delete fileManager;
}

void ProjectsManager::loadProject(QString path)
{
    QByteArray data = fileManager->readProject(path);

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QJsonValue name = obj.value("name");
    QJsonValue rows = obj.value("rows");
    QJsonValue cols = obj.value("cols");
    QJsonValue color = obj.value("color");

    QJsonArray cellsArray = obj.value("cells").toArray();
    QJsonArray unplacedBoxesArray = obj.value("unplaced").toArray();

    QVector <Cell*> cells;
    QVector <UnPlacedBox*> unPlacedBoxes;

    currentProject = new Project(name.toString(), rows.toInt(), cols.toInt(), color.toString(), editPage);

    for(int i = 0; i < cellsArray.size(); i++)
        cells.push_back(new Cell(currentProject->getLcd(), i, color.toString(), cellsArray[i].toObject().value("id").toInt(), cellsArray[i].toObject().value("value").toString()));

    for(int i = 0; i < unplacedBoxesArray.size(); i++)
    {
        if(i > 0)
            unPlacedBoxes.push_back(new UnPlacedBox(currentProject, editPage, unplacedBoxesArray[i].toObject().value("id").toInt(), unplacedBoxesArray[i].toObject().value("value").toString(), QPoint(820, unPlacedBoxes.last()->y() + 50)));
        else
            unPlacedBoxes.push_back(new UnPlacedBox(currentProject, editPage, unplacedBoxesArray[i].toObject().value("id").toInt(), unplacedBoxesArray[i].toObject().value("value").toString(), QPoint(820, 100)));
    }

    currentProject->loadCells(cells);
    currentProject->loadUnplacedBoxes(unPlacedBoxes);

    stackedWidget->setCurrentIndex(2);
}

void ProjectsManager::createProject(QString name, unsigned short rows, unsigned short cols, QColor color)
{
    currentProject = new Project(name, rows, cols, color, editPage);
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

    for(int i = 0; i < currentProject->getNumberOfUnplacedBoxes(); i++)
    {
        QJsonObject unPlacedBox;
        unPlacedBox.insert(idStr, QJsonValue(currentProject->getUnplacedBox(i)->getId()));
        unPlacedBox.insert(valueStr, QJsonValue(currentProject->getUnplacedBox(i)->getValue()));

        unPlacedBoxes.push_back(QJsonValue(unPlacedBox));
    }

    obj.insert(QString("name"), QJsonValue(currentProject->getName()));
    obj.insert(QString("rows"), QJsonValue(currentProject->getRows()));
    obj.insert(QString("cols"), QJsonValue(currentProject->getCols()));
    obj.insert(QString("color"), QJsonValue(currentProject->getColor()));

    obj.insert(QString("cells"), QJsonValue(cells));
    obj.insert(QString("unPlacedBoxes"), QJsonValue(unPlacedBoxes));

    doc.setObject(obj);

    fileManager->saveProject(&doc);
}

