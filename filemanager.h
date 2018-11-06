#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

#include <QTextStream>

#include <QString>

class Project;

class FileManager
{
private:
    QFile* file;
    QString path = "./projects.txt";
public:
    FileManager(){}
    FileManager(QString name);
    ~FileManager();

    void shortRead(); //read only projects names to show them in the homepage boxes

    void read(Project* project); //read the selected project
    void writeNewProject(Project* project); //write the edited project to the file
    void removeProject(Project* project);   //remove the project from the file

    bool fileExists(); //checks if the file with the path exists
};

#endif // FILEMANAGER_H
