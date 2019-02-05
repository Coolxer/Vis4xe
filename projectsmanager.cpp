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

    readBoxes();
}

ProjectsManager::~ProjectsManager()
{
    delete currentProject;
}

void ProjectsManager::readBoxes()
{
    boxes.clear();

    QByteArray data = fileManager.shortRead();

    if(data != nullptr)
    {

            prList->setCurrentIndex(0);
        }
        else
            prList->setCurrentIndex(1);

    }
}

void ProjectsManager::loadProject(ProjectNameBox* box, QString path)
{

    if(path.isEmpty())
    {
        path = QFileDialog::getOpenFileName(editPage, "Open File",
                                                           "",
                                                            "Json (*.json);;All Files (*)");
    }

    currentProject = DataConverter::convertToProject(fileManager.readProject(path));

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

    fileManager.saveProject(DataConverter::convertProjectToData(currentProject));
    fileManager.saveCutProject(DataConverter::convertCutProjectToData(this));

    readBoxes();
}

