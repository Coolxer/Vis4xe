#include "filemanager.h"

FileManager::~FileManager()
{
    delete fileDialog;
}

QByteArray FileManager::shortRead()
{
    projectsFile.setFileName("C:/Users/lukasz/Desktop/projects.json");

    if(!projectsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"failed to open file";

    QByteArray data = projectsFile.readAll();

    projectsFile.close();

    return data;
}

QByteArray FileManager::readProject(QString path)
{
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
       qDebug()<<"failed to Open file";
    else
       qDebug()<<"Opened file";

    QByteArray data = file.readAll();

    file.close();

    return data;
}

void FileManager::saveProject(QJsonDocument* project)
{
    //open fileWindow to select the path
    /*               */

    QString path = "randomowe.json";

    QFile file(path);

    if(!file.open(QFile::WriteOnly))
        qDebug()<<"failed to Open file";
     else
        qDebug()<<"Opened file";

    file.write(project->toJson());
}

void FileManager::removeProject(QString path)
{

}
