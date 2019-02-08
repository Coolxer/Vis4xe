#include "filemanager.h"

#include "projectsmanager.h"

FileManager::FileManager(ProjectsManager* projectsManager)
{
    this->projectsManager = projectsManager;

    documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    projectsFile.setFileName(documentsPath + "/Vis4xe/projects.json");
}

void FileManager::saveVisFile(QByteArray data)
{
    QFile file(projectsManager->getCurrentProject()->getVisPath());

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
            int x = i;

            do
            {
               if(projectsManager->getCurrentProject()->getLcd()->getCell(i)->getId() == -1)
                   break;

               current += projectsManager->getCurrentProject()->getLcd()->getCell(i)->text();

               i++;

            }while(1);

            out<<"\nlcd.setCursor("<<projectsManager->getCurrentProject()->getLcd()->getCell(x)->getCol()<<','<<projectsManager->getCurrentProject()->getLcd()->getCell(x)->getRow()<<");";
            out<<"\nlcd.print(\""<<current<<"\");";

            current = "";

            out<<"\n";
        }
    }

    file.close();
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

    if(file.exists())
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

    if(!dir.exists(projectsManager->getCurrentProject()->getDirPath()) && !projectsManager->getCurrentProject()->isSavedInFile())
        dir.mkdir(projectsManager->getCurrentProject()->getDirPath());

    saveVisFile(data);
    saveAvrFile();
}

void FileManager::saveCutProject(QByteArray data)
{
    QDir dir;

    if(!dir.exists(documentsPath + "/Vis4xe"))
        dir.mkdir(documentsPath + "/Vis4xe");

    if(!projectsFile.open(QIODevice::WriteOnly))
        return;

    projectsFile.write(data);

    projectsFile.close();
}




