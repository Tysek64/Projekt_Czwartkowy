#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H

#include <QString>
#include <QHash>
#include <opencv2/core.hpp>
#include <trackedobject.h>

class dataCollection
{
public:
    dataCollection();
    void init();
    void addItem (QString name);
    void removeItem(QString name);
    void removeActiveItem();
    QString getActiveName();
    trackedObject getActiveItem();
    void setActiveItem (QString name);
    int test();
    void setRect (trackedObject rect);

private:
    QHash<QString, trackedObject>* rects;
    QString activeItem;
};

#endif // DATACOLLECTION_H
