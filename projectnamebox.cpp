#include "projectnamebox.h"

#include "projectsmanager.h"

ProjectNameBox::ProjectNameBox(QWidget* parent, QString name, QString path, QPoint pos) : QLabel (parent)
{
    this->name = name;
    this->path = path;

    setGeometry(pos.x(), pos.y(), 200, 100);
    setStyleSheet("QLabel { border: 2px solid #0099ff; color: #0099ff; font-size:25px; border-radius:50px; }");
    setAlignment(Qt::AlignCenter);
    setText(name);
}

ProjectNameBox::~ProjectNameBox()
{

}

void ProjectNameBox::init(ProjectsManager* projectsManager)
{
    this->projectsManager = projectsManager;
}

void ProjectNameBox::mousePressEvent(QMouseEvent*)
{
    //open the edit mode with the correct / selected this project
    projectsManager->loadProject(this, path);
}

void ProjectNameBox::enterEvent(QEvent*)
{
    setStyleSheet("QLabel { background-color: #0099ff; font-size:25px; border-radius:50px; }");

    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void ProjectNameBox::leaveEvent(QEvent*)
{
    setStyleSheet("QLabel { border: 2px solid #0099ff; color: #0099ff; font-size:25px; border-radius:50px; }");

    QApplication::restoreOverrideCursor();
}
