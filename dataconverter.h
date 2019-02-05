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

public:
    DataConverter();

    static Project* convertToProject(QByteArray data);
    static QByteArray convertProjectToDocument(Project* project);
    static QByteArray convertCutProjectToDocument(ProjectsManager* projectsManager);
    static void convertToNameBoxes(ProjectsManager* projectsManager, QByteArray data);

    static QJsonObject convertVectorToJson(ProjectsManager* projectsManager);
};


#endif // DATACONVERTER_H
