#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QByteArray>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

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
    static QByteArray* convertProjectToDocument(Project* project);
    static QByteArray* convertCutProjectToDocument(Project* project);
    static void convertToNameBoxes(QByteArray data);
};


#endif // DATACONVERTER_H
