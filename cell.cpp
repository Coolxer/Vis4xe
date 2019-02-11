#include "cell.h"

#include "lcd.h"

Cell::Cell(Lcd* lcd, int index) : QLabel(lcd)
{
    this->lcd = lcd;
    this->index = index;

    row = (index / lcd->getCols()) + 1;
    //col = index - (row * lcd->getCols());

    col = index - ((row - 1) * lcd->getCols());

    init();
}

Cell::Cell(Lcd* lcd, int index, int id, QString value) : QLabel(lcd)
{
    this->lcd = lcd;
    this->index = index;

    this->id = id;

    init();

    setText(value);
}

void Cell::init()
{
    setMinimumSize(20, 30);
    setMaximumSize(20, 30);

    setAlignment(Qt::AlignCenter);

    setStyleSheet("QLabel{ background-color: #0099ff; font-size: 25px; }");
}

void Cell::enterEvent(QEvent*)
{
    if(!lcd->editEnabled())
    {
        setStyleSheet("QLabel { background-color : #ff8000; font-size: 25px; }");
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
    }
}

void Cell::leaveEvent(QEvent*)
{
    if(!lcd->editEnabled())
    {
        setStyleSheet("QLabel { background-color: #0099ff; font-size: 25px; }");
        QApplication::restoreOverrideCursor();
    }
}

void Cell::mousePressEvent(QMouseEvent*)
{
    if(id != -1)
        lcd->setSelectedCell(index);
}
