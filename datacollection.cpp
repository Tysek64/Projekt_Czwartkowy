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

void dataCollection::setActiveName (QString name) {
    activeItem = name;
}

void dataCollection::setActiveIten (trackedObject item) {
    rects->remove(activeItem);
    rects->insert(activeItem, item);
}

void dataCollection::removeActiveItem (bool withName) {
    rects->remove(activeItem);
    if (withName) {
        activeItem = NULL;
    }
}

int dataCollection::getSize() {
    int result = 0;
    for (QString k : rects->keys()) {
        result += rects->value(k).getSize();
    }

    return result;
}

int dataCollection::getHSize() {
    return rects->size();
}

trackedObject dataCollection::getObject(int index) {
    return rects->value(rects->keys()[index]);
}

void dataCollection::setRect (trackedObject rect) {
    rects->insert(activeItem, rect);
}

cv::Rect dataCollection::getImage (int frame) {
    for (QString k : rects->keys()) {
        if (frame < rects->value(k).getSize()) {
            return rects->value(k).getRectIndex(frame);
        } else {
            frame -= rects->value(k).getSize();
        }
    }

    return *new cv::Rect(-1, -1, -1, -1);
}

int dataCollection::getFrameNo (int frame) {
    for (QString k : rects->keys()) {
        if (frame < rects->value(k).getSize()) {
            return rects->value(k).getFrameNo(frame);
        } else {
            frame -= rects->value(k).getSize();
        }
    }

    return -1;
}

float dataCollection::getConfidence (int frame) {
    for (QString k : rects->keys()) {
        if (frame < rects->value(k).getSize()) {
            return rects->value(k).getConfidence(frame);
        } else {
            frame -= rects->value(k).getSize();
        }
    }

    return -1;
}

trackedObject dataCollection::getItem(int frame) {
    for (QString k : rects->keys()) {
        if (frame < rects->value(k).getSize()) {
            return rects->value(k);
        } else {
            frame -= rects->value(k).getSize();
        }
    }

    return *new trackedObject();
}
