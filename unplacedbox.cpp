#include "unplacedbox.h"

#include "project.h"

UnPlacedBox::UnPlacedBox(Project* project, int id, QString text, QPoint pos): QLabel(project->getContainer())
{
    this->project = project;
    this->id = id;
    startPosition = pos;

    dragBox = new DragBox(this, QPoint(pos.x() - 35, pos.y()));
    delBox = new DelBox(this, QPoint(pos.x() + 115, pos.y()));

    setGeometry(pos.x(), pos.y(), 110, 30);
    setStyleSheet("QLabel{border: 3px solid #FFFFFF; color: #FFFFFF; }");
    setText(text);
    setAlignment(Qt::AlignCenter);

    project->setSaved(false);
}

UnPlacedBox::~UnPlacedBox()
{
    setVisible(false);

    dragBox->setVisible(false);
    delete dragBox;

    delBox->setVisible(false);
    delete delBox;
}

void UnPlacedBox::checkDrop(QPoint point)
{
    dragBoxPoint = point;

    if(project->writeOnLcd(this))
        show(false);
    else
        dragBox->reset();
}

void UnPlacedBox::remove()
{
    project->getStringsWidget()->deleteStringWidget(id);
    project->setSaved(false);
}

void UnPlacedBox::show(bool x)
{
    setVisible(x);
    dragBox->setVisible(x);
    delBox->setVisible(x);
}

void UnPlacedBox::reset()
{
    move(startPosition);
    dragBox->reset();
    delBox->reset();
    show(true);
}

