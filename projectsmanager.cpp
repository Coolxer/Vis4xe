#include "projectsmanager.h"

#include <QStackedWidget>

#include "projectnamebox.h"
#include "cell.h"
#include "unplacedbox.h"

ProjectsManager::ProjectsManager(QWidget* homePage, QWidget* editPage, QStackedWidget* stackedWidget, QStackedWidget* prList, QPushButton* saveButton)
{
    this->homePage = homePage;
    this->editPage = editPage;
    this->stackedWidget = stackedWidget;
    this->prList = prList;

    this->saveButton = saveButton;

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

    bool ok = DataConverter::convertToNameBoxes(this, fileManager->shortRead());

    if(!ok)
        fileManager->saveCutProject(DataConverter::convertVectorToData(this));

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
    {
        stackedWidget->setCurrentIndex(2);
        currentProject->setSaved(true);
    }

    if(currentProject == nullptr && box != nullptr)
        box->setBlocked();
}

void ProjectsManager::createProject(QString name, int rows, int cols)
{
    currentProject = new Project(name, rows, cols, editPage, saveButton);
}

void ProjectsManager::saveProject()
{
    currentProject->setPath(QFileDialog::getSaveFileName(editPage, "Open File",
                                                   currentProject->getName(),
                                                    "Json (*.json);;All Files (*)"));

    if(currentProject->getVisPath().isEmpty())
        return;

    fileManager->saveProject(DataConverter::convertProjectToData(currentProject));
    if(DataConverter::convertCutProjectToData(this) != nullptr)
        fileManager->saveCutProject(DataConverter::convertCutProjectToData(this));

    readBoxes();

    currentProject->setSaved(true);
}

