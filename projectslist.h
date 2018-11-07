#ifndef PROJECTSLIST_H
#define PROJECTSLIST_H

#include <QVector>

#include "project.h"

#include "filemanager.h"

class ProjectsList
{
private:
    FileManager fileManager;
    QVector <Project*> list;

    QVector <QString*> names;

    int index = -1; //the index of the current selected project // -1 means none

public:
    ProjectsList();

    void addProject(Project* project);
    void saveProject(Project* project);
    void removeProject(Project* project);

    Project* getCurrentProject() { return list[index]; } //returns the pointer to the current project

    void setCurrentProject(Project* project); //sets the index of the current project

};

#endif // PROJECTSLIST_H
