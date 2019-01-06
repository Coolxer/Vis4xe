#include "cell.h"

#include "lcd.h"

Cell::Cell(Lcd* lcd, int index, QColor color) : QLabel(lcd)
{
    this->lcd = lcd;
    this->index = index;
    this->color = color;

    init();
}

Cell::Cell(Lcd* lcd, int index, QColor color, int id, QString value) : QLabel(lcd)
{
    this->lcd = lcd;
    this->index = index;
    this->color = color;

    this->id = id;

    init();

    setText(value);
}

void Cell::init()
{
    setMinimumSize(20, 30);
    setMaximumSize(20, 30);

    setAlignment(Qt::AlignCenter);

    QString styles = "QLabel{ background-color: %1; font-size: 25px; }";
    setStyleSheet(styles.arg(color.name()));
}

Cell::~Cell()
{
    //delete lcd;
}

void Cell::enterEvent(QEvent*)
{
    int r, g, b;
    qDebug()<<color.rgb();

    QString style = "QLabel { background-color : %1; font-size: 25px; }";

    //setStyleSheet(style.arg());
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void Cell::leaveEvent(QEvent*)
{
    QString styles = "QLabel { background-color: %1; font-size: 25px; }";
    setStyleSheet(styles.arg(color.name()));

    QApplication::restoreOverrideCursor();
}

void Cell::mousePressEvent(QMouseEvent*)
{
    lcd->setSelectedCell(index);
    //setStyleSheet("QLabel { background-color: #ff0000; font-size: 25px; }");
}
