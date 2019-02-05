#ifndef PROJECTSLIST_H
#define PROJECTSLIST_H

#include <QVector>

#include "filemanager.h"
#include "dataconverter.h"
#include "project.h"

class ProjectNameBox;
class QWidget;
class QStackedWidget;

class ProjectsManager
{
private:
    FileManager* fileManager; //the pointer , dynamic object which is managing the file service

    QWidget* homePage; //the pointer to homePage to manage pages
    QWidget* editPage; //the pointer to EditPage to manage pages
    QStackedWidget* stackedWidget; //the pointer to stackedWidget to manage pages

    QStackedWidget* prList; //the pointer to stackedWidget to eventually display communnicate "No projects found..."

    QVector <ProjectNameBox*> boxes; //the boxes that represents last opened projects, for fast opening...

    Project* currentProject = nullptr; //the pointer to the current opened project

    void readBoxes();//reads the boxes from projects.json file and puts them on the homePage screen

public:
    ProjectsManager(){}
    ProjectsManager(QWidget* homePage, QWidget* editPage, QStackedWidget* stackedWidget, QStackedWidget* prList);
    ~ProjectsManager();

    Project* getCurrentProject() { return currentProject; } //returns the pointer to the current project

    QVector <ProjectNameBox*> getBoxes() { return boxes; }

    void loadProject(ProjectNameBox* box, QString path); //function to loadProject from file after clicked on the Name box
    void createProject(QString name, int rows, int cols); //the function that creates the new Project and opening it
    void saveProject(); //the function to saveProject to file, this runs the fileManager service

    void releaseProject() { delete currentProject; currentProject = nullptr; } //the function that's closing current opened project

    void setBoxes(QVector<ProjectNameBox*> boxes) { this->boxes = boxes; }
    void addBox(ProjectNameBox* box) { boxes.push_back(box); }

    QWidget* getHomePage() { return homePage; }
    QWidget* getEditPage() { return editPage; }
};

#endif // PROJECTSLIST_H
