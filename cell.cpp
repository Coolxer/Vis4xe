#include "cell.h"

#include "lcd.h"

Cell::Cell(Lcd* lcd, int index) : QLabel(lcd)
{
    this->lcd = lcd;
    this->index = index;

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

Cell::~Cell()
{
    //delete lcd;
}

void Cell::enterEvent(QEvent*)
{
    if(!lcd->editEnabled())
    {
        setStyleSheet("QLabel { background-color : #006bb3; font-size: 25px; }");
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
    //setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
}
