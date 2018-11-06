#include "filemanager.h"

FileManager::FileManager(QString name)
{
    file = new QFile(name);

    //if(!fileExists())


}

FileManager::~FileManager()
{
    delete file;
}

void FileManager::read()
{
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file->atEnd())
    {
        QByteArray line = file->readLine();
        //process_line(line);
    }
}

void FileManager::writeNewProject(Project* project)
{
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(file);

    //write there everything like name, color, cells values
    //out << "The magic number is: " << 49 << "\n";
}

void FileManager::removeProject(Project* project)
{
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
}

bool FileManager::fileExists()
{
    QFileInfo check_file(path);

    if(check_file.exists() && check_file.isFile())
        return true;

    return false;
}
