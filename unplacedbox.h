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

    QPoint startPosition;
    QPoint offset;
    QPoint lastPosition;

    QLabel* grabBox;

    int id;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    UnPlacedBox(Project* project, QWidget* parent, int id, QString text, QPoint pos);
    ~UnPlacedBox();

    QPoint getStartPosition() { return startPosition; }
    QPoint getLastPosition() { return lastPosition; }

    int getId() { return id; }
};

#endif // UNPLACEDBOX_H
