#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QColor>
#include <QString>

class MyLabel : public QLabel
{
    Q_OBJECT
private:
    QColor color;
    QString string;
public:
     MyLabel(QWidget* parent = nullptr, QString string = "", QColor color = Qt::red) : QLabel(parent){ this->string = string ; this->color = color; this->setText(this->string); };
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
