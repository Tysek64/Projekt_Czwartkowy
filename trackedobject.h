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
    void addRect(int frame, cv::Rect rect, bool force);
    cv::Rect getRect(int frame);
    int getSize();
    cv::Rect getRectIndex (int index);

private:
    QString name;
    int startFrame;
    int endFrame;
    QHash<int, cv::Rect>* rects;
};

#endif // TRACKEDOBJECT_H
