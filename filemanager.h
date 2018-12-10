#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QtDebug>

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

#include <QTextStream>
#include <QString>
#include <QByteArray>

#include <QJsonDocument>

class FileManager
{
private:
    QFile projectsFile;
    QFile currentProjectFile;
    QFileDialog* fileDialog;

public:
    FileManager(){};
    ~FileManager();

    QByteArray shortRead();//read only projects names and paths to show them in the homepage boxes

    QByteArray readProject(QString path); //read the selected project

    void saveProject(QJsonDocument* project); //write the project to file

    void removeProject(QString path);   //remove the project from the file

};

#endif // FILEMANAGER_H
