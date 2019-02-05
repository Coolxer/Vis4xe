#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>

#include <QStandardPaths>

#include <QTextStream>
#include <QByteArray>

#include "dataconverter.h"

class ProjectsManager;

class FileManager
{
private:
    QDir dir;
    QFile projectsFile;
    QString documentsPath;

    ProjectsManager* projectsManager;

    void saveVisFile(QByteArray data);
    void saveAvrFile();

public:
    FileManager(){}
    FileManager(ProjectsManager* projectsManager);

    QByteArray shortRead();//read only projects names and paths to show them in the homepage's boxes

    QByteArray readProject(QString path); //read the selected project

    void saveProject(QByteArray data); //write the project to file
    void saveCutProject(QByteArray data); //saves only name an path of the project to the projectsList file

    void removeProject(QString path);   //remove the project from the file

};

#endif // FILEMANAGER_H
