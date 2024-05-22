#include "trackedobject.h"
#include <QDebug>

trackedObject::trackedObject() {
    name = *new QString("test");
    startFrame = 0;
    endFrame = 3000;
    labelClass = -1;
    labelType = -1;
    rects = new QHash<int, cv::Rect>();
}

void trackedObject::addRect (int frame, cv::Rect rect, bool force) {
    if ((frame >= startFrame && frame <= endFrame) && (!rects->contains(frame) || force)) {
        rects->insert(frame, rect);
    }
}

void trackedObject::removeRect (int frame) {
    if (((frame >= startFrame) && (frame <= endFrame)) && (rects->contains(frame))) {
        rects->remove(frame);
    }
}

void trackedObject::setName (QString name) {
    this->name = name;
}

void trackedObject::setStart (int frame) {
    startFrame = frame;

    for (int k : rects->keys()) {
        if (k < frame) {
            rects->remove(k);
        }
    }
}

void trackedObject::setEnd (int frame) {
    endFrame = frame;

    for (int k : rects->keys()) {
        if (k > frame) {
            rects->remove(k);
        }
    }
}

void trackedObject::setClass (int labelClass) {
    this->labelClass = labelClass;
}

void trackedObject::setType (int labelType) {
    this->labelType = labelType;
}

int trackedObject::getStart () {
    return this->startFrame;
}

int trackedObject::getEnd () {
    return this->endFrame;
}

int trackedObject::getClass () {
    return this->labelClass;
}

int trackedObject::getType () {
    return this->labelType;
}

cv::Rect trackedObject::getRect (int frame) {
    return rects->value(frame);
}

int trackedObject::getSize() {
    return rects->size();
}

cv::Rect trackedObject::getRectIndex (int index) {
    for (int k : rects->keys()) {
        if (index == 0) {
            return rects->value(k);
        } else {
            index--;
        }
    }

    return *new cv::Rect(-1, -1, -1, -1);
}

int trackedObject::getFrameNo (int index) {
    for (int k : rects->keys()) {
        if (index == 0) {
            return k;
        } else {
            index--;
        }
    }

    return -1;
}
