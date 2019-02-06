#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QByteArray>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QVector>

#include "qwidget.h"
#include "qfiledialog.h"

class ProjectsManager;
class Project;
class UnPlacedBox;
class Cell;
class ProjectNameBox;

class DataConverter
{
private:
    static QJsonObject convertVectorToJson(ProjectsManager* projectsManager); //converts the c++ <Vector> to json array type

public:
    DataConverter();

    static Project* convertToProject(ProjectsManager* projectsManager, QByteArray data); //converts json data from File to project
    static QByteArray convertProjectToData(Project* project); //converts project to json format to save it in file
    static QByteArray convertCutProjectToData(ProjectsManager* projectsManager); //converts the shortcut of project to save it in projectsList file
    static void convertToNameBoxes(ProjectsManager* projectsManager, QByteArray data); //converts the json array boxes to their program types


};


#endif // DATACONVERTER_H
