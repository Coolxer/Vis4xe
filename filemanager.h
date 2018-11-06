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

    void read();
    void writeNewProject(Project* project);
    void removeProject(Project* project);

    bool fileExists();
};

#endif // FILEMANAGER_H
