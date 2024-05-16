#ifndef TRACKEDOBJECT_H
#define TRACKEDOBJECT_H

#include <QHash>
#include <opencv2/core.hpp>

class trackedObject
{
public:
    trackedObject();
    void setName(QString name);
    void setStart (int frame);
    void setEnd (int frame);
    void setClass (int labelClass);
    void setType (int labelType);
    int getStart();
    int getEnd();
    int getClass();
    int getType();
    void addRect(int frame, cv::Rect rect, bool force);
    cv::Rect getRect(int frame);
    int getSize();
    cv::Rect getRectIndex (int index);
    int getFrameNo (int index);

private:
    QString name;
    int startFrame;
    int endFrame;
    int labelClass;
    int labelType;
    QHash<int, cv::Rect>* rects;
};

#endif // TRACKEDOBJECT_H
