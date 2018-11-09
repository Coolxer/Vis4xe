#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QtDebug>

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

#include <QTextStream>
#include <QString>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class ProjectsList;

class Project;

class FileManager
{
private:
    QFile* file;
    QFileDialog* fileDialog;
    QString projectsInfoPath = "C:/Users/lukasz/Desktop/projects.json";

    QJsonDocument doc;

    QByteArray data;
    QJsonObject obj;
    QJsonValue value;

    QJsonArray jArray;

    //QJsonDocument doc;
    //QJsonObject obj;

    ProjectsList* projectsList;

public:
    FileManager(){}
    FileManager(ProjectsList* projectsList);
    ~FileManager();

    void shortRead(); //read only projects names to show them in the homepage boxes
    void read(Project* project); //read the selected project

    void writeNewProject(Project* project); //write the edited project to the file
    void updateProject(Project* project); //write the edited project to the file

    void removeProject(Project* project);   //remove the project from the file

    bool fileExists(); //checks if the file with the path exists
};

#endif // FILEMANAGER_H
