#include "projectnamebox.h"

ProjectNameBox::ProjectNameBox(QWidget* parent, QString name, QString path, int id): QLabel (parent)
{
    this->name = name;
    this->path = path;
    this->id = id;

    setGeometry(200, 200, 200, 100);
    setStyleSheet("QLabel { border: 2px solid #0099ff; color: #0099ff;");
    setText(name);
}

void ProjectNameBox::mousePressEvent(QMouseEvent* event)
{
    //open the edit mode with the correct / selected this project
}
