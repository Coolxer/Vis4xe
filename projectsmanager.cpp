#include "projectsmanager.h"

ProjectsManager::ProjectsManager(QWidget* homePage, QWidget* editPage) : fileManager(homePage, editPage)
{
    this->homePage = homePage;
    this->editPage = editPage;

    boxes = fileManager.shortRead();

   // for(int i = 0; i <boxes.length(); i++)
   //     boxes[i]->showPath();
}

ProjectsManager::~ProjectsManager()
{
    delete currentProject;
    delete homePage;

    delete editPage;
}

void ProjectsManager::loadProject(QString path)
{
    qDebug()<<"clicked";
    //currentProject = fileManager.read(path);
    fileManager.readProject(path);
}
