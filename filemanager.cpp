#include "filemanager.h"

#include "projectsmanager.h"

FileManager::FileManager(ProjectsManager* projectsManager)
{
    this->projectsManager = projectsManager;
}

QByteArray FileManager::shortRead()
{
    QByteArray data = nullptr;

    projectsFile.setFileName("C:/Users/lukasz/Desktop/projects.json");

    if(projectsFile.exists())
    {

        if(!projectsFile.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug()<<"failed to open file";

        data = projectsFile.readAll();

        projectsFile.close();
    }

    return data;
}

QByteArray FileManager::readProject(QString path)
{
    QFile file(path);
    QByteArray data = nullptr;

    if (file.exists())
    {
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
           qDebug()<<"Opened file";

        data = file.readAll();

        file.close();
    }

    return data;
}

void FileManager::saveProject(QByteArray data)
{
    QDir dir;

    dir.mkdir(projectsManager->getCurrentProject()->getDirPath());

    saveVisFile(data);
    saveAvrFile();
}

void FileManager::saveCutProject(QByteArray data)
{
    if(!projectsFile.exists())
        return;

    if(!projectsFile.open(QIODevice::ReadWrite))
        return;

    projectsFile.write(data);

    projectsFile.close();
}

void FileManager::removeProject(QString path)
{

}

void FileManager::saveVisFile(QByteArray data)
{
    QFile file;

    file.setFileName(projectsManager->getCurrentProject()->getVisPath());

    if(file.open(QFile::WriteOnly))
        return;

    file.write(data);

    file.close();
}

void FileManager::saveAvrFile()
{
    QFile file;

    file.setFileName(projectsManager->getCurrentProject()->getAvrPath());

    if(!file.open(QFile::WriteOnly| QIODevice::Text))
        return;

    QTextStream out(&file);

    QString current = "";

    out<<"lcd.begin("<<projectsManager->getCurrentProject()->getLcd()->getCols()<<','<<projectsManager->getCurrentProject()->getLcd()->getRows()<<");\n";

    for(int i = 0; i < projectsManager->getCurrentProject()->getLcd()->getNumberOfCells(); i++)
    {
        if(projectsManager->getCurrentProject()->getLcd()->getCell(i)->getId() != -1)
        {
            do
            {
               if(projectsManager->getCurrentProject()->getLcd()->getCell(i)->getId() == -1)
                   break;

               current += projectsManager->getCurrentProject()->getLcd()->getCell(i)->text();

               i++;

            }while(1);

            out<<"\nlcd.print(\""<<current<<"\");";

            current = "";

            out<<"\n";
        }
    }

    file.close();
}

