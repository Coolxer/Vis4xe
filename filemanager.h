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

#include <QVector>

class ProjectNameBox;
class Project;

class FileManager
{
private:
    QFile projectsFile;
    QFile currentProjectFile;
    QFileDialog* fileDialog;

    QWidget* homePage;
    QWidget* editPage;

public:
    FileManager(){}
    FileManager(QWidget* homePage, QWidget* editPage);
    ~FileManager();

    QVector <ProjectNameBox*> shortRead();//read only projects names and paths to show them in the homepage boxes

    Project* readProject(QString path); //read the selected project

    void saveProject(Project* project); //write the project to file

    void removeProject(QString path);   //remove the project from the file

    bool fileExists(); //checks if the file with the path exists
};

#endif // FILEMANAGER_H
