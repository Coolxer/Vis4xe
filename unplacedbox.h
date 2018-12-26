#ifndef UNPLACEDBOX_H
#define UNPLACEDBOX_H

#include <QApplication>
#include <QMouseEvent>
#include <QLabel>
#include <QString>
#include <QPoint>

#include <QtDebug>

#include <QDrag>
#include <QMimeData>

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

    QLabel* stringBox;
    QLabel* delBox;

    int id;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

public:
    UnPlacedBox(Project* project, int id, QString text, QPoint pos);
    ~UnPlacedBox();

    QPoint getStartPosition() { return startPosition; }
    QPoint getLastPosition() { return lastPosition; }

    int getId() { return id; }
    QString getValue() { return text(); }

};

#endif // UNPLACEDBOX_H
