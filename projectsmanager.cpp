#include "projectsmanager.h"

ProjectsManager::ProjectsManager(QWidget* widget)
{
    this->widget = widget;
}

ProjectsManager::~ProjectsManager()
{
    delete widget;
}

void ProjectsManager::addProject(Project* project)
{
    list.push_back(project);
}


void ProjectsManager::removeProject(Project* project)
{
    //fileManager.removeProject(project);
    //list.removeAt()
}

void ProjectsManager::setCurrentProject(Project* project)
{
    index = list.indexOf(project, 1);
}
