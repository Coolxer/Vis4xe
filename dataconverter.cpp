#include "dataconverter.h"

#include "project.h"
#include "unplacedbox.h"
#include "cell.h"
#include "projectnamebox.h"

DataConverter::DataConverter()
{

}

Project* DataConverter::convertToProject(QByteArray data)
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

    project = new Project(obj.value("name").toString(), obj.value("rows").toInt(), obj.value("cols").toInt(), editPage);

    for(int i = 0; i < cellsArray.size(); i++)
        cells.push_back(new Cell(project->getLcd(), i, cellsArray[i].toObject().value("id").toInt(), cellsArray[i].toObject().value("value").toString()));

    for(int i = 0; i < unplacedBoxesArray.size(); i++)
    {
        if(i > 0)
            unPlacedBoxes.push_back(new UnPlacedBox(project, unplacedBoxesArray[i].toObject().value("id").toInt(), unplacedBoxesArray[i].toObject().value("value").toString(), QPoint(810, unPlacedBoxes.last()->y() + 40)));
        else
            unPlacedBoxes.push_back(new UnPlacedBox(project, unplacedBoxesArray[i].toObject().value("id").toInt(), unplacedBoxesArray[i].toObject().value("value").toString(), QPoint(810, 5)));
    }

    project->loadCells(cells);
    project->loadUnplacedBoxes(unPlacedBoxes);


    return project;

}

QByteArray* DataConverter::convertProjectToDocument(Project* project)
{
    QJsonDocument doc;
    QJsonObject obj;

    QJsonArray cells;
    QJsonArray unPlacedBoxes;

    QJsonObject cell;

    for(int i = 0; i < project->getLcd()->getNumberOfCells(); i++)
    {
        cell.insert("id", QJsonValue(project->getLcd()->getCell(i)->getId()));
        cell.insert("value", QJsonValue(project->getLcd()->getCell(i)->text()));

        cells.push_back(QJsonValue(cell));
    }

    QJsonObject unPlacedBox;

    for(int i = 0; i < project->getStringsWidget()->getAmount(); i++)
    {

        unPlacedBox.insert("id", QJsonValue(project->getStringsWidget()->getBox(i)->getId()));
        unPlacedBox.insert("value", QJsonValue(project->getStringsWidget()->getBox(i)->text()));

        unPlacedBoxes.push_back(QJsonValue(unPlacedBox));
    }

    obj.insert(QString("name"), QJsonValue(project->getName()));
    obj.insert(QString("rows"), QJsonValue(project->getLcd()->getRows()));
    obj.insert(QString("cols"), QJsonValue(project->getLcd()->getCols()));

    obj.insert(QString("cells"), QJsonValue(cells));
    obj.insert(QString("unPlacedBoxes"), QJsonValue(unPlacedBoxes));

    doc.setObject(obj);

    QString fileName = QFileDialog::getSaveFileName(editPage, "Open File",
                                                   currentProject->getName(),
                                                    "Json (*.json);;All Files (*)");




    return &doc.toJson();
}

QByteArray* DataConverter::convertCutProjectToDocument(Project* project)
{
    QJsonDocument doc;
    QJsonObject obj;
    QJsonObject item;

    item.insert(QString("name"), QJsonValue(project->getName()));
    item.insert(QString("path"), QJsonValue(fileName));

    boxesArray.push_back(item);

    obj.insert(QString("projects"), boxesArray);

    doc.setObject(obj);

    return &doc.toJson();
}

void DataConverter::convertToNameBoxes(QByteArray data)
{

}
