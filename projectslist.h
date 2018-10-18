#ifndef PROJECTSLIST_H
#define PROJECTSLIST_H

#include <QVector>

#include "project.h"

class ProjectsList
{
private:
    QVector <Project> list;
public:
    ProjectsList();

    void addProject(Project* project);
    void deleteProject(Project* project);

};

#endif // PROJECTSLIST_H
