#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QColor>
#include <QString>

class Cell : public QLabel
{
    Q_OBJECT

private:
    QColor color;
    QString string;

    int id = -1; //that means the the cell is empty // none string here

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
        setStyleSheet("QLabel { background-color : #ff7733; }");
    }

    void leaveEvent(QEvent *event) override
    {
        setStyleSheet("QLabel { background-color : #0099ff; }");
    }
};

#endif // CELL_H
