#ifndef TRACKEDOBJECT_H
#define TRACKEDOBJECT_H

#include <QHash>
#include <opencv2/core.hpp>
#include <opencv2/video/tracking.hpp>

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
    void addRect(int frame, cv::Rect rect, float confidence, bool force);
    void removeRect(int frame);
    cv::Rect getRect(int frame);
    int getSize();
    cv::Rect getRectIndex (int index);
    int getFrameNo (int index);
    float getConfidence (int index);
    void initTracker (cv::Mat frame, cv::Rect& roi);
    float updateTracker (cv::Mat frame, cv::Rect& roi);

private:
    QString name;
    int startFrame;
    int endFrame;
    int labelClass;
    int labelType;
    QHash<int, QPair<cv::Rect, float>>* rects;
    cv::Ptr<cv::TrackerVit> tracker;
};

#endif // TRACKEDOBJECT_H
