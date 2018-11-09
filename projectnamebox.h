#ifndef PROJECTNAMEBOX_H
#define PROJECTNAMEBOX_H

#include <QLabel>
#include <QMouseEvent>

class ProjectNameBox : public QLabel
{
private:
    int id;
    QString name;
    QString path;
protected:
    void mousePressEvent(QMouseEvent* event);
public:
    ProjectNameBox() {}
    ProjectNameBox(QWidget* parent, QString name, QString path, int id);
};

#endif // PROJECTNAMEBOX_H
