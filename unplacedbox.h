#ifndef UNPLACEDBOX_H
#define UNPLACEDBOX_H

#include <QApplication>
#include <QMouseEvent>
#include <QLabel>
#include <QString>
#include <QPoint>

class Project;

class UnPlacedBox : public QLabel
{
private:
    Project* project;

    QPoint offset;
    QPoint currentPosition;
    QPoint lastPosition;

    QLabel* grabBox;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    UnPlacedBox(Project* project, QWidget* parent, QString text, QPoint pos);
    ~UnPlacedBox();
};

#endif // UNPLACEDBOX_H
