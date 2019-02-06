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

    bool blocked = false;

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

public:
    ProjectNameBox() {}
    ProjectNameBox(ProjectsManager* projectsManager, QString name, QString path, QPoint pos);

    void setPosition(QPoint p);
    QString getName() { return text(); }
    QString getPath() { return path; }

    void setBlocked();
};

#endif // PROJECTNAMEBOX_H
