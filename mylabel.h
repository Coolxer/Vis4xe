#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QColor>

class MyLabel : public QLabel
{
    Q_OBJECT
private:
    QColor color;
public:
     MyLabel(QWidget* parent = nullptr, QColor color = Qt::red) : QLabel(parent){ this->color = color; };

protected:
    void enterEvent(QEvent *ev) override
    {
        setStyleSheet("QLabel { background-color : #ff7733; }");
    }

    void leaveEvent(QEvent *ev) override
    {
        setStyleSheet("QLabel { background-color : #0099ff; }");
    }
};

#endif // MYLABEL_H
