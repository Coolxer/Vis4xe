#include "cell.h"

#include "lcd.h"

Cell::Cell(Lcd* lcd, int index, QColor color) : QLabel(lcd)
{
    this->lcd = lcd;
    this->index = index;
    this->color = color;

    setMinimumSize(20, 30);
    setMaximumSize(20, 30);

    setAlignment(Qt::AlignCenter);

    QString styles = "QLabel{ background-color: %1; }";
    setStyleSheet(styles.arg(color.name()));
}

Cell::Cell(Lcd* lcd, int index, QColor color, int id, QString value) : QLabel(lcd)
{
    this->lcd = lcd;
    this->index = index;
    this->color = color;

    this->id = id;

    setMinimumSize(20, 30);
    setMaximumSize(20, 30);

    setAlignment(Qt::AlignCenter);

    QString styles = "QLabel{ background-color: %1; }";
    setStyleSheet(styles.arg(color.name()));

    setText(value);
}

Cell::~Cell()
{
    //delete lcd;
}

void Cell::enterEvent(QEvent*)
{
    lcd->setHoveredCell(index);

    setStyleSheet("QLabel { background-color : #ff7733; font-size: 25px; }");
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void Cell::leaveEvent(QEvent*)
{
    setStyleSheet("QLabel { background-color : #0099ff; font-size: 25px; }");
    QApplication::restoreOverrideCursor();
}

void Cell::mousePressEvent(QMouseEvent*)
{
    lcd->setSelectedCell(index);
    //setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
}
