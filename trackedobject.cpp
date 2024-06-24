#include "trackedobject.h"
#include <QDebug>

trackedObject::trackedObject() {
    name = *new QString("test");
    startFrame = 0;
    endFrame = 3000;
    labelClass = -1;
    labelType = -1;
    rects = new QHash<int, QPair<doubleRect, float>>();
    try {
        tracker = cv::TrackerVit::create();
        trackerPresent = true;
    } catch (cv::Exception e) {
        trackerPresent = false;
    }
}

void trackedObject::initTracker (cv::Mat frame, cv::Rect& roi) {
    if (trackerPresent) {
        tracker->init(frame, roi);
    }
}

float trackedObject::updateTracker (cv::Mat frame, cv::Rect& roi) {
    if (trackerPresent) {
        tracker->update(frame, roi);
        return tracker->getTrackingScore();
    } else {
        return 0.0f;
    }
}

void trackedObject::addRect (int frame, doubleRect rect, float confidence, bool force) {
    if ((frame >= startFrame && frame <= endFrame) && (!rects->contains(frame) || force)) {
        rects->insert(frame, *new QPair<doubleRect, float>(rect, confidence));
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

doubleRect trackedObject::getRect (int frame) {
    return rects->value(frame).first;
}

int trackedObject::getSize() {
    return rects->size();
}

doubleRect trackedObject::getRectIndex (int index) {
    for (int k : rects->keys()) {
        if (index == 0) {
            return rects->value(k).first;
        } else {
            index--;
        }
    }

    return *new doubleRect(-1, -1, -1, -1);
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

float trackedObject::getConfidence (int index) {
    for (int k : rects->keys()) {
        if (index == 0) {
            return rects->value(k).second;
        } else {
            index--;
        }
    }

    return -1;
}

bool trackedObject::getTracker () {
    return trackerPresent;
}
