#include "stringslist.h"

StringsList::StringsList(QWidget* widget)
{
    this->widget = widget;
}

StringsList::~StringsList()
{
    delete widget;
}

void StringsList::addString(QString string)
{
    list.push_back(new MyLabel(widget, string));
    list.back()->setStyleSheet("MyLabel { border: 2px solid #0099ff; }");
}

void StringsList::deleteString(MyLabel* label)
{
    int index = list.indexOf(label);
    list.removeAt(index);
}

void StringsList::changeString(MyLabel* label, QString newString)
{
    int index = list.indexOf(label);
    list[index]->setText(newString);
}
