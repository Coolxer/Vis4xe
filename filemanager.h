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


class FileManager
{
private:
    QFile projectsFile;

public:
    FileManager(){}

    QByteArray shortRead();//read only projects names and paths to show them in the homepage's boxes

    QByteArray readProject(QString path); //read the selected project

    void saveProject(QJsonDocument project, QJsonDocument projectsList, QString fileName); //write the project to file

    void removeProject(QString path);   //remove the project from the file

};

#endif // FILEMANAGER_H
