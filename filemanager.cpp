#include "filemanager.h"

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

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

void FileManager::saveProject(QJsonDocument project, QJsonDocument projectsList, QString fileName)
{
    QFile vFile;
    QFile aFile;
    QDir dir;

    QString sDir="";

    QString vName = "";
    QString aName = "";

    for(int i = 0; i <= fileName.length() - 6; i++)
        sDir += fileName[i];

    int x = 0;

    //vName
    for(int i = fileName.length() -1; i>=0; i--)
    {
        if(fileName[i] == '/')
            break;

        x++;
    }

    int k = fileName.length() - 1 - x;

    for(int i = k; i<=fileName.length()-1; i++)
        vName += fileName[i];


    //aName
    for(int i = 0; i <= vName.length() - 1; i++)
    {
        if(vName[i] == '.')
            break;

        aName += vName[i];
    }

    aName += ".txt";

    dir.mkdir(sDir);
    vFile.setFileName(sDir + vName);
    aFile.setFileName(sDir + aName);


    if(!vFile.open(QFile::WriteOnly))
        qDebug()<<"failed to Open file";

    vFile.write(project.toJson());

    vFile.close();

    if(!aFile.open(QFile::WriteOnly| QIODevice::Text))
        qDebug()<<"failed to Open file";


    QJsonObject obj = project.object();

    int rows = obj.value("rows").toInt();
    int cols = obj.value("cols").toInt();

    QJsonArray cellsArray = obj.value("cells").toArray();

    QTextStream out(&aFile);

    QString current = "";

    out<<"lcd.begin("<<cols<<','<<rows<<");\n";

    for(int i = 0; i < cellsArray.size(); i++)
    {
        QJsonObject o = cellsArray[i].toObject();

        if(o.value("id").toInt() != -1)
        {
            do
            {
               if(cellsArray[i].toObject().value("id").toInt() == -1)
                   break;

               current += cellsArray[i].toObject().value("value").toString();

               i++;

            }while(1);

            //out<<"\nlcd.setCursor("<<o.value("")<<','<<row<<");";
            out<<"\nlcd.print(\""<<current<<"\");";

            current = "";

            out<<"\n";
        }
    }


    aFile.close();

    if (projectsFile.exists())
    {
        if(!projectsFile.open(QIODevice::ReadWrite))
            qDebug()<<"failed opened the file";

        projectsFile.write(projectsList.toJson());

        projectsFile.close();
    }
}

void FileManager::removeProject(QString path)
{

}
