#include "stringslist.h"

StringsList::StringsList(QWidget* widget, QVector <MyLabel*> xCells)
{
    this->widget = widget;

    cells = xCells;

    addString("piora");
    addString("cykle");
    addString("kat obrotu");
    addString("Predkosc");
    showList();

}

StringsList::~StringsList()
{
    delete widget;
}

void StringsList::addString(QString string)
{
    list.push_back(new DraggableLabel(widget, string, cells));
    list.back()->setStyleSheet("DraggableLabel { border: 2px solid #0099ff; font-size: 20px; }");
}

void StringsList::deleteString(DraggableLabel* label)
{
    unsigned short index = list.indexOf(label);
    list.removeAt(index);
}

void StringsList::changeString(DraggableLabel* label, QString newString)
{
    unsigned short index = list.indexOf(label);
    list[index]->setText(newString);
}

void StringsList::showList()
{
    for(unsigned short i = 0, j = 100; i < list.length(); i++, j+=50)
    {
        list[i]->setGeometry(QRect(0, 0, 125, 30));
        list[i]->setAlignment(Qt::AlignCenter);
        list[i]->move(820, j);
        list[i]->show();
    }
}
