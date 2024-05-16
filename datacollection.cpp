#include "datacollection.h"
#include <QDebug>

dataCollection::dataCollection() {
    rects = new QHash<QString, trackedObject>();
    activeItem = *new QString();
}

void dataCollection::addItem (QString name) {
    qDebug() << 'a';
    rects->insert(name, *new trackedObject());
}

void dataCollection::removeItem (QString name) {
    rects->remove(name);
}

QString dataCollection::getActiveName() {
    return activeItem;
}

trackedObject dataCollection::getActiveItem () {
    return rects->value(activeItem);
}

void dataCollection::setActiveItem (QString name) {
    activeItem = name;
}

void dataCollection::removeActiveItem () {
    rects->remove(activeItem);
    activeItem = NULL;
}

int dataCollection::test() {
    return rects->size();
}

void dataCollection::setRect (trackedObject rect) {
    rects->insert(activeItem, rect);
}
