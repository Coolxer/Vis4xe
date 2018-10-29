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
    unsigned short id = 0;

public:
     MyLabel(QWidget* parent = nullptr, QString string = "", unsigned short id = 0, QColor color = Qt::red) : QLabel(parent)
     {
         this->string = string ;
         this->id = id;
         this->color = color;
         this->setText(this->string);
     }

protected:
    void enterEvent(QEvent *event) override
    {
        setStyleSheet("QLabel { background-color : #ff7733; }");
    }

    void leaveEvent(QEvent *event) override
    {
        setStyleSheet("QLabel { background-color : #0099ff; }");
    }
};

#endif // MYLABEL_H
