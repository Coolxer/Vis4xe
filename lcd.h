#ifndef LCD_H
#define LCD_H

#include <QColor>

class Lcd
{
private:
    unsigned short rows;
    unsigned short cols;

    QColor color;

public:
    Lcd(){};
    Lcd(unsigned short rows, unsigned short cols, QColor color);
};

#endif // LCD_H
