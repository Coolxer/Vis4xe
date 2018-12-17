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

class QWidget;

class FileManager
{
private:
    QFile projectsFile;
    QFile currentProjectFile;

    QWidget* widget;

public:
    FileManager();
    FileManager(QWidget* widget);
    ~FileManager();

    QByteArray shortRead();//read only projects names and paths to show them in the homepage boxes

    QByteArray readProject(QString path); //read the selected project

    void saveProject(QJsonDocument* project, QString name); //write the project to file

    void removeProject(QString path);   //remove the project from the file

};

#endif // FILEMANAGER_H
