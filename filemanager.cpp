#include "filemanager.h"

#include "projectnamebox.h"
#include "project.h"

FileManager::FileManager(QWidget* homePage, QWidget* editPage)
{
    this->homePage = homePage;
    this->editPage = editPage;
}

FileManager::~FileManager()
{
    delete fileDialog;
    delete homePage;
    delete editPage;
}

QVector <ProjectNameBox*> FileManager::shortRead()
{
    QVector <ProjectNameBox*> boxes;

    projectsFile.setFileName("C:/Users/lukasz/Desktop/projects.json");

    if(!projectsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"failed to open file";

    QByteArray data = projectsFile.readAll();

    projectsFile.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.object()["projects"].toArray();

    for(int i = 0; i < array.size(); i++)
        boxes.push_back(new ProjectNameBox(homePage, array[i].toObject().value("name").toString(), array[i].toObject().value("path").toString(), QPoint(20 + (220) *i, 100)));

    return boxes;
}

Project* FileManager::readProject(QString path)
{
    QFile file(path);

    Project* project = nullptr;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
       qDebug()<<"failed to Open file";
    else
       qDebug()<<"Opened file";

    //return nullptr;

    QByteArray data = file.readAll();

    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonObject obj = doc.object();

    QJsonValue name = obj.value("name");
    QJsonValue rows = obj.value("rows");
    QJsonValue cols = obj.value("cols");
    QJsonValue color = obj.value("color");

    QJsonArray cellsArray = obj.value("cells").toArray();
    QJsonArray unplacedBoxes = obj.value("unplaced").toArray();

    return project;
}

void FileManager::saveProject(Project* project)
{
    //file = fileDialog->getOpenFileName(projectsList->getWidget(), tr("save project"))

    /*
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(file);

    //write there everything like name, color, cells values
    //out << "The magic number is: " << 49 << "\n";
    */
}

void FileManager::removeProject(QString path)
{

}

bool FileManager::fileExists()
{
    /*
    QFileInfo check_file(path);

    if(check_file.exists() && check_file.isFile())
        return true;

    */
    return false;
}
