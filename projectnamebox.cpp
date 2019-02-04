#include "projectnamebox.h"

#include "projectsmanager.h"

ProjectNameBox::ProjectNameBox(ProjectsManager* projectsManager, QWidget* parent, QString name, QString path, QPoint pos) : QLabel (parent)
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
