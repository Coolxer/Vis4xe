#ifndef PROJECTNAMEBOX_H
#define PROJECTNAMEBOX_H

#include <QLabel>
#include <QMouseEvent>

class ProjectNameBox : public QLabel
{
private:
    int id;
protected:
    void mousePressEvent(QMouseEvent* event);
public:
    ProjectNameBox(QWidget* parent, QString text, int id);
};

#endif // PROJECTNAMEBOX_H
