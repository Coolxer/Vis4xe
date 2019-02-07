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

    bool blocked = false; //the state of the nameBox, blocked = file with the project not exists

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

public:
    ProjectNameBox() {}
    ProjectNameBox(ProjectsManager* projectsManager, QString name, QString path, QPoint pos);

    QString getName() { return text(); }
    QString getPath() { return path; }

    void setBlocked(); //blocks the box after program noticed that the selected file not exists
};

#endif // PROJECTNAMEBOX_H
