#include "filemanager.h"

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

QByteArray FileManager::shortRead()
{
    QByteArray data = nullptr;

    projectsFile.setFileName("C:/Users/lukasz/Desktop/projects.json");

    if(projectsFile.exists())
    {

        if(!projectsFile.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug()<<"failed to open file";

        data = projectsFile.readAll();

        projectsFile.close();

    }

    return data;
}

QByteArray FileManager::readProject(QString path)
{
    QFile file(path);
    QByteArray data = nullptr;

    if (file.exists())
    {
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
           qDebug()<<"Opened file";

        data = file.readAll();

        file.close();
    }

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

    if (projectsFile.exists())
    {
        if(!projectsFile.open(QIODevice::ReadWrite))
            qDebug()<<"failed opened the file";

        projectsFile.write(projectsList.toJson());

        projectsFile.close();
    }
}

void FileManager::removeProject(QString path)
{

}
