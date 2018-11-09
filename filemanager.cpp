#include "filemanager.h"

#include "projectslist.h"

FileManager::FileManager(ProjectsList* projectsList)
{
    file = new QFile(projectsInfoPath);

    this->projectsList = projectsList;

    //shortRead();
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    data = file->readAll();
    doc = doc.fromJson(data);
    obj = doc.object();
    value = obj.value("projects");

    jArray = value.toArray();

    //QJsonValue value =

    QJsonObject jObj;

    qDebug()<<projectsList->getList().length();

    foreach (const QJsonValue & v, jArray)
    {
        jObj = v.toObject();
        //qDebug()<<v.toObject().value("name");
        projectsList->getList().push_back(new Project(jObj.value("name").toString(), jObj.value("rows").toInt(), jObj.value("cols").toInt(), QColor(255, 255, 255, 0), projectsList->getWidget()));
    }

    qDebug()<<projectsList->getList().length();
}

FileManager::~FileManager()
{
    delete file;
    delete fileDialog;

    delete projectsList;
}

/*
void FileManager::shortRead()
{
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!file->atEnd())
    {
        QByteArray line = file->readLine();
    }
}
*/

void FileManager::read(Project* project)
{
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    else
    {
        QByteArray data = file->readAll();
        QJsonDocument doc = doc.fromJson(data);
        QJsonObject obj = doc.object();
        QJsonValue value = obj.value("projects");

        QJsonArray jArray = value.toArray();

        qDebug()<<jArray;
    }
}

void FileManager::writeNewProject(Project* project)
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

void FileManager::updateProject(Project* project)
{

}

void FileManager::removeProject(Project* project)
{
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
}

bool FileManager::fileExists()
{
    QFileInfo check_file(projectsInfoPath);

    if(check_file.exists() && check_file.isFile())
        return true;

    return false;
}
