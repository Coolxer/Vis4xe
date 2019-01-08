#ifndef PROJECTSLIST_H
#define PROJECTSLIST_H

#include <QByteArray>
#include <QVector>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "filemanager.h"

#include "project.h"

#include <QFileDialog>

class ProjectNameBox;
class QWidget;
class QStackedWidget;

class ProjectsManager
{
private:
    FileManager* fileManager;

    QWidget* homePage;
    QWidget* editPage;
    QStackedWidget* stackedWidget;

    QVector <ProjectNameBox*> boxes;

    Project* currentProject = nullptr;

    QJsonArray boxesArray;

    void readBoxes();

public:
    ProjectsManager(){}
    ProjectsManager(QWidget* homePage, QWidget* editPage, QStackedWidget* stackedWidget);
    ~ProjectsManager();

    Project* getCurrentProject() { return currentProject; } //returns the pointer to the current project

    QVector <ProjectNameBox*> getBoxes() { return boxes; }

    void loadProject(QString path);
    void createProject(QString name, unsigned short rows, unsigned short cols);
    void saveProject();

    void releaseProject() { delete currentProject; currentProject = nullptr; }
};

#endif // PROJECTSLIST_H
