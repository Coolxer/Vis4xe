#include "projectnamebox.h"

#include "projectsmanager.h"

ProjectNameBox::ProjectNameBox(ProjectsManager* projectsManager, QString name, QString path, QPoint pos) : QLabel (projectsManager->getHomePage())
{
    this->projectsManager = projectsManager;
    this->path = path;

    setGeometry(pos.x(), pos.y(), 200, 100);
    setStyleSheet("QLabel { border: 2px solid #0099ff; color: #0099ff; font-size:25px; border-radius:50px; }");
    setAlignment(Qt::AlignCenter);
    setText(name);
}

void ProjectNameBox::mousePressEvent(QMouseEvent*)
{
    if(!blocked)
        projectsManager->loadProject(this, path);
}

void ProjectNameBox::enterEvent(QEvent*)
{
    if(!blocked)
        setStyleSheet("QLabel { background-color: #0099ff; font-size:25px; border-radius:50px; }");

    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void ProjectNameBox::leaveEvent(QEvent*)
{
    if(!blocked)
        setStyleSheet("QLabel { border: 2px solid #0099ff; color: #0099ff; font-size:25px; border-radius:50px; }");

    QApplication::restoreOverrideCursor();
}

void ProjectNameBox::setBlocked()
{
    setEnabled(false);
    blocked = true;
    setText(text() + "\nNOT FOUND!");
    setStyleSheet("QLabel { border: 2px solid red; color: red; font-size:25px; border-radius:50px; opacity: 0.5;}");
}


