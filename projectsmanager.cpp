#include "projectsmanager.h"

#include <QStackedWidget>

#include "projectnamebox.h"
#include "cell.h"
#include "unplacedbox.h"

ProjectsManager::ProjectsManager(QWidget* homePage, QWidget* editPage, QStackedWidget* stackedWidget, QStackedWidget* prList)
{
    this->homePage = homePage;
    this->editPage = editPage;
    this->stackedWidget = stackedWidget;
    this->prList = prList;

    fileManager = new FileManager(this);

    readBoxes();
}

ProjectsManager::~ProjectsManager()
{
    delete currentProject;
}

void ProjectsManager::readBoxes()
{
    boxes.clear();

    DataConverter::convertToNameBoxes(this, fileManager->shortRead());

    if(boxes.length() == 0)
        prList->setCurrentIndex(1);
    else
        prList->setCurrentIndex(0);
}

void ProjectsManager::loadProject(ProjectNameBox* box, QString path)
{
    if(path.isEmpty())
    {
        path = QFileDialog::getOpenFileName(editPage, "Open File",
                                                           "",
                                                            "Json (*.json);;All Files (*)");
    }

    currentProject = DataConverter::convertToProject(this, fileManager->readProject(path));

    if(currentProject != nullptr)
        stackedWidget->setCurrentIndex(2);
    else if (box != nullptr)
    {
        box->hide();
        delete box;
        boxes.removeLast();

        if(boxes.length() <= 0 )
            prList->setCurrentIndex(1);
    }
}

void ProjectsManager::createProject(QString name, unsigned short rows, unsigned short cols)
{
    currentProject = new Project(name, rows, cols, editPage);
}

void ProjectsManager::saveProject()
{
    currentProject->setPath(QFileDialog::getSaveFileName(currentProject->getContainer(), "Open File",
                                                   currentProject->getName(),
                                                    "Json (*.json);;All Files (*)"));

    if(currentProject->getDirPath().isEmpty())
        return;

    fileManager->saveProject(DataConverter::convertProjectToData(currentProject));
    fileManager->saveCutProject(DataConverter::convertCutProjectToData(this));

    readBoxes();
}

