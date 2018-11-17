#ifndef PROJECTNAMEBOX_H
#define PROJECTNAMEBOX_H

#include <QApplication>

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

#include <QDebug>

class ProjectsManager;

class ProjectNameBox : public QLabel
{
private:
    QString name;
    QString path;

    ProjectsManager* projectsManager;

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

public:
    ProjectNameBox() {}
    ProjectNameBox(QWidget* parent, QString name, QString path, QPoint pos);
    ~ProjectNameBox();

    void init(ProjectsManager* projectsManager);
};

#endif // PROJECTNAMEBOX_H
