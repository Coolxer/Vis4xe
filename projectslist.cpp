#include "projectslist.h"

ProjectsList::ProjectsList()
{
    if(fileManager.fileExists())
        fileManager.shortRead();
}

void ProjectsList::addProject(Project* project)
{
    fileManager.writeNewProject(project);
}

void ProjectsList::removeProject(Project* project)
{
    fileManager.removeProject(project);
}
