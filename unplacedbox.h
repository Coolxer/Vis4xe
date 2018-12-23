#ifndef UNPLACEDBOX_H
#define UNPLACEDBOX_H

#include <QApplication>
#include <QMouseEvent>
#include <QLabel>
#include <QString>
#include <QPoint>

#include <QtDebug>

class Project;
class QWidget;

class UnPlacedBox : public QLabel
{
private:
    Project* project;
    QWidget* listWidget;

    QPoint startPosition;
    QPoint offset;
    QPoint lastPosition;

    QLabel* dragBox;
    QLabel* delBox;

    int id;

    bool insideList = true;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    UnPlacedBox(Project* project, QWidget* widget, int id, QString text, QPoint pos);
    ~UnPlacedBox();

    QPoint getStartPosition() { return startPosition; }
    QPoint getLastPosition() { return lastPosition; }

    int getId() { return id; }
    QString getValue() { return text(); }

};

#endif // UNPLACEDBOX_H
