#include "filemanager.h"

#include "projectsmanager.h"

FileManager::FileManager(ProjectsManager* projectsManager)
{
    this->projectsManager = projectsManager;

    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir dir;

    if(!dir.exists(documentsPath))
        dir.mkdir(documentsPath + "/Vis4xe");

    projectsFile.setFileName(dir.path() + "/projects.json");
}

QByteArray FileManager::shortRead()
{
    QByteArray data = nullptr;

    if(projectsFile.exists())
    {
        if(projectsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            data = projectsFile.readAll();

            projectsFile.close();
        }
    }

    return data;
}

QByteArray FileManager::readProject(QString path)
{
    QFile file(path);
    QByteArray data = nullptr;

    if (file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            data = file.readAll();

            file.close();
        }
    }

    return data;
}

void FileManager::saveProject(QByteArray data)
{
    QDir dir;

    if(dir.mkdir(projectsManager->getCurrentProject()->getDirPath()))
    {
        saveVisFile(data);
        saveAvrFile();
    }
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
    QFile file(projectsManager->getCurrentProject()->getVisPath());

    qDebug()<<projectsManager->getCurrentProject()->getVisPath();

    if(!file.open(QFile::WriteOnly))
        return;

    file.write(data);

    file.close();
}

void FileManager::saveAvrFile()
{
    QFile file(projectsManager->getCurrentProject()->getAvrPath());

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

