#include "projectslist.h"

ProjectsList::ProjectsList()
{
    if(fileManager.fileExists())
        fileManager.shortRead();


}

void ProjectsList::addProject(Project* project)
{
    list.push_back(project);
    fileManager.writeNewProject(project);
}

void ProjectsList::saveProject(Project* project)
{
    fileManager.updateProject(project);
}

void ProjectsList::removeProject(Project* project)
{
    fileManager.removeProject(project);
    //list.removeAt()
}

void ProjectsList::setCurrentProject(Project* project)
{
    index = list.indexOf(project, 1);
}
