#ifndef STRINGSLIST_H
#define STRINGSLIST_H

#include <QString>
#include <QStringList>

class StringsList
{
private:
    QString test = "maly";
    QStringList list;
public:
    StringsList();

    void addString();
    void deleteString();
    void changeString();

    QString getString(unsigned short index) { return list.at(index); };

};

#endif // STRINGSLIST_H
