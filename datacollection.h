#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H

#include <QString>
#include <QHash>
#include <opencv2/core.hpp>
#include <trackedobject.h>
#include <doublerect.h>

class dataCollection
{
public:
    dataCollection();
    void init();
    bool addItem (QString name);
    void removeItem(QString name);
    void removeActiveItem(bool withName);
    QString getActiveName();
    trackedObject getActiveItem();
    trackedObject getObject (int index);
    void setActiveName (QString name);
    void setActiveIten (trackedObject item);
    int test();
    void setRect (trackedObject rect);
    int getSize();
    int getHSize();
    doubleRect getImage(int frame);
    int getFrameNo(int frame);
    float getConfidence (int frame);
    trackedObject getItem(int frame);

private:
    QHash<QString, trackedObject>* rects;
    QString activeItem;
};

#endif // DATACOLLECTION_H
