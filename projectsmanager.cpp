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
        QJsonDocument doc = QJsonDocument::fromJson(data);

        boxesArray = doc.object()["projects"].toArray();

        if(boxesArray.size() > 0 )
        {
            int firstElement = 0;
            int count = boxesArray.size();

            if(boxesArray.size() > 9)
            {
                firstElement = boxesArray.size() - 9;
                count = 9;
            }

            int r = count / 3;

            if(count % 3 != 0)
                r++;

            int lastItemColumn = count % 3;

            if(lastItemColumn == 0)
                lastItemColumn = 3;

            if(r == 1)
            {
                if(lastItemColumn == 1)
                    lastItemColumn = 2;
                else if (lastItemColumn == 2)
                    lastItemColumn = 1;
            }

            int c = 3;

            if(count< c)
                c = lastItemColumn;

            int m = 0;

            for(int i = 0; i < r; i++)
            {
                if(i == r-1)
                    c = lastItemColumn;

                for(int j = 0; j < c; j++)
                {
                    boxes.push_back(new ProjectNameBox(this, homePage, boxesArray[firstElement].toObject().value("name").toString(), boxesArray[m].toObject().value("path").toString(), QPoint(120 + (260 *j), (120 * i) + 100)));

                    m++;
                    firstElement++;
                }
            }
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
    fileManager.saveProject(DataConverter::convertProjectToDocument(currentProject));
    fileManager.saveCutProject(DataConverter::convertCutProjectToDocument(currentProject));

    readBoxes();
}

