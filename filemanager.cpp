#include "filemanager.h"

FileManager::FileManager(QWidget* widget)
{
   this->widget = widget;
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

void FileManager::saveProject(QJsonDocument* project, QString name)
{
    QString fileName = QFileDialog::getSaveFileName(widget, "Open File",
                                                    name,
                                                    "Json (*.json);;All Files (*)");
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly))
        qDebug()<<"failed to Open file";
     else
        qDebug()<<"Opened file";

    file.write(project->toJson());
}

void FileManager::removeProject(QString path)
{

}
