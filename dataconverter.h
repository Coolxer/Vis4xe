#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QByteArray>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QVector>

#include <QFileInfo>

class ProjectsManager;
class Project;
class UnPlacedBox;
class Cell;
class ProjectNameBox;

class DataConverter
{
private:
    static QJsonObject convertVectorToJsonObject(ProjectsManager* projectsManager); //converts the c++ <Vector> to json array type

public:
    DataConverter();

    static Project* convertToProject(ProjectsManager* projectsManager, QByteArray data); //converts json data from File to project
    static QByteArray convertProjectToData(Project* project); //converts project to json format to save it in file
    static QByteArray convertCutProjectToData(ProjectsManager* projectsManager); //converts the shortcut of project to save it in projectsList file
    static bool convertToNameBoxes(ProjectsManager* projectsManager, QByteArray data); //converts the json array boxes to their program types

    static QByteArray convertVectorToData(ProjectsManager* projectsManager); //converts QVector<> to QByteArray data type ready to save in txt file
};


#endif // DATACONVERTER_H
