#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

#include <QTextStream>
#include <QByteArray>

#include <QStandardPaths>

#include "dataconverter.h"

class ProjectsManager;

class FileManager
{
private:
    ProjectsManager* projectsManager; //the pointer to the ProjectsManager

    QString documentsPath; //the path of the user Documents folder (C:\Users\user)
    QFile projectsFile; //the projectsListFile that includes the short description of the created projects

    void saveVisFile(QByteArray data); //method that saves the data to the json file (readable by Vis4xe)
    void saveAvrFile(); //method that saves the algorithm of arduino instructions to use with LCD screen (using LiquidCrystal library) to text (*.txt) file

public:
    FileManager(){}
    FileManager(ProjectsManager* projectsManager);

    QByteArray shortRead();//read only projects names and paths to show them in the homepage's boxes

    QByteArray readProject(QString path); //read the selected project

    void saveProject(QByteArray data); //write the project to file
    void saveCutProject(QByteArray data); //saves only name an path of the project to the projectsList file
};

#endif // FILEMANAGER_H
