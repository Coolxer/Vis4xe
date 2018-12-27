#include "delbox.h"

#include "unplacedbox.h"

DelBox::DelBox(UnPlacedBox* unPlacedBox, QWidget* parent, QPoint pos): QLabel(parent)
{
    this->unPlacedBox = unPlacedBox;

    setGeometry(pos.x(), pos.y(), 30, 30);
    setStyleSheet("QLabel{border: 3px solid #FF0000; border-radius: 15px; font-size: 16px; color: #FFFFFF; }");
    setText("X");
    setAlignment(Qt::AlignCenter);

    show();
}

void DelBox::mousePressEvent(QMouseEvent* event)
{
    setVisible(false);
    unPlacedBox->remove();
}

void DelBox::enterEvent(QEvent*)
{
    setStyleSheet("QLabel{ background-color: #FF0000; border-radius: 15px; font-size: 16px; color: #FFFFFF;}");
    unPlacedBox->setStyleSheet("QLabel{ background-color: #FF0000; color: #FFFFFF; }");
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void DelBox::leaveEvent(QEvent*)
{
    setStyleSheet("QLabel{ border: 3px solid #FF0000; border-radius: 15px; font-size: 16px; color: #FFFFFF; }");
    unPlacedBox->setStyleSheet("QLabel{ border: 3px solid #0099ff; color: #FFFFFF; }");
    QApplication::restoreOverrideCursor();
}
