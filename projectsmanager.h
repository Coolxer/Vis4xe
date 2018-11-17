#ifndef PROJECTSLIST_H
#define PROJECTSLIST_H

#include <QVector>

#include "filemanager.h"

#include "project.h"
#include "projectnamebox.h"

class ProjectsManager
{
private:
    FileManager fileManager;

    QWidget* homePage;
    QWidget* editPage;

    int currentProjectIndex = -1; //the index of the current selected project // -1 means none

    QVector <ProjectNameBox*> boxes;

    Project* currentProject = nullptr;

public:
    ProjectsManager(){}
    ProjectsManager(QWidget* homePage, QWidget* editPage);
    ~ProjectsManager();

    Project* getCurrentProject() { return currentProject; } //returns the pointer to the current project

    QVector <ProjectNameBox*> getBoxes() { return boxes; }

    void loadProject(QString path);

};

#endif // PROJECTSLIST_H
