#ifndef PROJECTNAMEBOX_H
#define PROJECTNAMEBOX_H

#include <QApplication>
#include <QLabel>
#include <QMouseEvent>

class QWidget;
class ProjectsManager;

class ProjectNameBox : public QLabel
{
private:
    ProjectsManager* projectsManager;//the pointer to the projectstManager
    QString path; //the path to the project file(using if user clicked property box)

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

public:
    ProjectNameBox() {}
    ProjectNameBox(ProjectsManager* projectsManager, QWidget* parent, QString name, QString path, QPoint pos);
};

#endif // PROJECTNAMEBOX_H
