#include "filemanager.h"

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

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

void FileManager::saveProject(QJsonDocument project, QJsonDocument projectsList, QString fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly))
        qDebug()<<"failed to Open file";
     else
        qDebug()<<"Opened file";

    file.write(project.toJson());

    file.close();

    if(!projectsFile.open(QIODevice::ReadWrite))
        qDebug()<<"failed opened the file";


    projectsFile.write(projectsList.toJson());


}

void FileManager::removeProject(QString path)
{

}
