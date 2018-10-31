#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QColor>
#include <QString>

#include <QApplication>

class Cell : public QLabel
{
    Q_OBJECT

private:
    QColor color; // the color of the cell (inherited(got) from lcd)
    QString string; //the letter of the QLabel, normally its null = ""

    int id = -1;//this variable get you know if it is written to any string
                //that means the the cell is empty // none string here

public:
     Cell(QWidget* parent = nullptr, QColor color = Qt::red) : QLabel(parent)
     {
         this->string = string ;
         this->color = color;
         this->setText(this->string);
     }

     void setId(int id) { this->id = id; };
     int getId() { return id; };

protected:
    void enterEvent(QEvent *event) override
    {
        setStyleSheet("QLabel { background-color : #ff7733; font-size: 25px; }");
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
    }

    void leaveEvent(QEvent *event) override
    {
        setStyleSheet("QLabel { background-color : #0099ff; font-size: 25px; }");
        QApplication::restoreOverrideCursor();
    }
};

#endif // CELL_H
