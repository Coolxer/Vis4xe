#ifndef PROJECTSLIST_H
#define PROJECTSLIST_H

#include <QVector>

#include "project.h"

#include "filemanager.h"

class ProjectsList
{
private:
    FileManager fileManager;
    QVector <Project> list;
public:
    ProjectsList();

    void addProject(Project* project);
    void removeProject(Project* project);

};

#endif // PROJECTSLIST_H
