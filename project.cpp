#include "project.h"

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color, QWidget* widget)
                : lcd(rows, cols, color, widget)
{

}

