#include "project.h"

Project::Project(QString name, unsigned short rows, unsigned short cols, QColor color)
                : lcd(rows, cols, color)
{

}

