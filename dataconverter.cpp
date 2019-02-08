#include "dataconverter.h"

#include "projectsmanager.h"
#include "project.h"
#include "unplacedbox.h"
#include "cell.h"
#include "projectnamebox.h"

QJsonObject DataConverter::convertVectorToJsonObject(ProjectsManager* projectsManager)
{
    QJsonArray array;
    QJsonObject obj, item;

    int n = projectsManager->getBoxes().size();

    for(int i = 0; i < n; i++)
    {
        item.insert(QString("name"), QJsonValue(projectsManager->getBoxes().at(i)->getName()));
        item.insert(QString("path"), QJsonValue(projectsManager->getBoxes().at(i)->getPath()));

        array.push_back(item);
    }

    obj.insert(QString("projects"), array);

    return obj;
}

Project* DataConverter::convertToProject(ProjectsManager* projectsManager, QByteArray data)
{
    if(data == nullptr)
        return nullptr;

    Project* project;

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QJsonArray cellsArray = obj.value("cells").toArray();
    QJsonArray unplacedBoxesArray = obj.value("unPlacedBoxes").toArray();

    QVector <Cell*> cells;
    QVector <UnPlacedBox*> unPlacedBoxes;

    project = new Project(obj.value("name").toString(), obj.value("rows").toInt(), obj.value("cols").toInt(), projectsManager->getEditPage(), projectsManager->getSaveButton());

    for(int i = 0; i < cellsArray.size(); i++)
        cells.push_back(new Cell(project->getLcd(), i, cellsArray[i].toObject().value("id").toInt(), cellsArray[i].toObject().value("value").toString()));

    for(int i = 0; i < unplacedBoxesArray.size(); i++)
    {
        if(i > 0)
            unPlacedBoxes.push_back(new UnPlacedBox(project, i, unplacedBoxesArray[i].toObject().value("id").toInt(), unplacedBoxesArray[i].toObject().value("value").toString(), QPoint(810, unPlacedBoxes.last()->y() + 40)));
        else
            unPlacedBoxes.push_back(new UnPlacedBox(project, 0, unplacedBoxesArray[i].toObject().value("id").toInt(), unplacedBoxesArray[i].toObject().value("value").toString(), QPoint(810, 10)));
    }

    project->getLcd()->loadCellsFromFile(cells);
    project->getStringsList()->loadBoxesFromFile(unPlacedBoxes);

    return project;
}

QByteArray DataConverter::convertProjectToData(Project* project)
{
    QJsonDocument doc;
    QJsonObject obj;

    QJsonArray cells;
    QJsonArray unPlacedBoxes;

    QJsonObject cell;

    for(int i = 0; i < project->getLcd()->getNumberOfCells(); i++)
    {
        cell.insert(QString("id"), QJsonValue(project->getLcd()->getCell(i)->getId()));
        cell.insert(QString("value"), QJsonValue(project->getLcd()->getCell(i)->text()));

        cells.push_back(QJsonValue(cell));
    }

    QJsonObject unPlacedBox;

    for(int i = 0; i < project->getStringsList()->getAmount(); i++)
    {

        unPlacedBox.insert(QString("id"), QJsonValue(project->getStringsList()->getBox(i)->getId()));
        unPlacedBox.insert(QString("value"), QJsonValue(project->getStringsList()->getBox(i)->text()));

        unPlacedBoxes.push_back(QJsonValue(unPlacedBox));
    }

    obj.insert(QString("name"), QJsonValue(project->getName()));
    obj.insert(QString("rows"), QJsonValue(project->getLcd()->getRows()));
    obj.insert(QString("cols"), QJsonValue(project->getLcd()->getCols()));

    obj.insert(QString("cells"), QJsonValue(cells));
    obj.insert(QString("unPlacedBoxes"), QJsonValue(unPlacedBoxes));

    doc.setObject(obj);

    return doc.toJson();
}

QByteArray DataConverter::convertCutProjectToData(ProjectsManager* projectsManager)
{
    QJsonObject o = convertVectorToJsonObject(projectsManager);
    QJsonArray array = o.value("projects").toArray();

    QJsonDocument doc;
    QJsonObject item;
    QJsonObject obj;

    item.insert(QString("name"), QJsonValue(projectsManager->getCurrentProject()->getName()));
    item.insert(QString("path"), QJsonValue(projectsManager->getCurrentProject()->getVisPath()));

    for(int i = 0; i < array.size(); i++)
        if(array[i].toObject().value("name") == item.value("name"))
            return nullptr;

    array.push_back(item);

    obj.insert(QString("projects"), array);

    doc.setObject(obj);

    return doc.toJson();
}

bool DataConverter::convertToNameBoxes(ProjectsManager* projectsManager, QByteArray data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.object()["projects"].toArray();
    QVector <ProjectNameBox*> boxes;

    bool allRight = true;

    int count = array.size();

    QVector <int> indexes;

    for(int i = 0; i < count; i++)
    {
        if(!QFileInfo::exists(array[i].toObject().value("path").toString()))
        {
            allRight = false;
            //array.removeAt(i);

            //count--;
            indexes.push_back(i);
        }
    }

    if(!allRight)
    {
        for(int i = 0; i < indexes.length(); i++)
            array.removeAt(indexes[i]);

        count = array.size();
    }

    if(count <= 0)
        return true;
    else if (count > 0 && count < 9)
    {
        int rows = count / 3;

        if(count % 3 != 0)
            rows++;

        int lastItemColumn = count % 3;

        if(lastItemColumn == 0)
            lastItemColumn = 3;

        int c = 3;

        if(count < 3)
            c = lastItemColumn;

        int m = 0;

        for(int i = 0; i < rows; i++)
        {
            if(i == rows - 1)
                c = lastItemColumn;

            for(int j = 0; j < c; j++)
            {
                boxes.push_back(new ProjectNameBox(projectsManager, array[m].toObject().value("name").toString(), array[m].toObject().value("path").toString(), QPoint(120 + (260 *j), (120 * i) + 100)));
                m++;
            }
        }
    }
    else if (count >= 9)
    {
        int currentElement = count - 9;
        count = 9;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                 boxes.push_back(new ProjectNameBox(projectsManager, array[currentElement].toObject().value("name").toString(), array[currentElement].toObject().value("path").toString(), QPoint(120 + (260 *j), (120 * i) + 100)));
                 currentElement++;
            }
        }
    }

    projectsManager->setBoxes(boxes);

    return allRight;

}

QByteArray DataConverter::convertVectorToData(ProjectsManager* projectsManager)
{
    QJsonObject obj = convertVectorToJsonObject(projectsManager);
    QJsonDocument doc;

    doc.setObject(obj);

    return doc.toJson();
}

