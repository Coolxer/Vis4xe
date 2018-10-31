#include "editmode.h"

#include "lcd.h"

EditMode::EditMode(Lcd* lcd, QString string)
{
    this->lcd = lcd;
    this->string = string;

    qDebug()<<"editMode constr";
}

EditMode::~EditMode()
{
    //delete lcd; //if i would decomment this line the debuqer/ compilator will throw an error
    qDebug()<<"editMode de-constr";
}
