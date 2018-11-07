#include "projectnamebox.h"

ProjectNameBox::ProjectNameBox(QWidget* parent, QString text, int id): QLabel (parent)
{
    this->id = id;

    setGeometry(200, 200, 200, 100);
    setStyleSheet("QLabel { border: 2px solid #0099ff; color: #0099ff;");
    setText(text);
}

void ProjectNameBox::mousePressEvent(QMouseEvent* event)
{
    //open the edit mode with the correct / selected this project
}
