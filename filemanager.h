#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QtDebug>
#include <QString>

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>

#include <QTextStream>
#include <QByteArray>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "dataconverter.h"

class FileManager
{
private:
    QFile projectsFile;

public:
    FileManager(){}

    QByteArray shortRead();//read only projects names and paths to show them in the homepage's boxes

    QByteArray readProject(QString path); //read the selected project

    void saveProject(QByteArray data); //write the project to file
    void saveCutProject(QByteArray data); //saves only name an path of the project to the projectsList file

    void removeProject(QString path);   //remove the project from the file

};

#endif // FILEMANAGER_H
