#ifndef PROJECTSLIST_H
#define PROJECTSLIST_H

#include <QVector>

#include "project.h"
#include "projectnamebox.h"

class QWidget;


class ProjectsManager
{
private:
    QVector <Project*> list;

    int index = -1; //the index of the current selected project // -1 means none

    QWidget* widget;

    QVector <ProjectNameBox*> boxes;

public:
    ProjectsManager(){}
    ProjectsManager(QWidget* widget);
    ~ProjectsManager();

    void addProject(Project* project);
    void removeProject(Project* project);

    Project* getCurrentProject() { return list[index]; } //returns the pointer to the current project

    void setCurrentProject(Project* project); //sets the index of the current project

    QVector <Project*> getList() { return list; }

    QWidget* getWidget() { return widget; }

    QVector <ProjectNameBox*> getBoxes() { return boxes; }

};

#endif // PROJECTSLIST_H
