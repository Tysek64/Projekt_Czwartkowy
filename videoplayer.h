#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QLabel>
#include <opencv2/videoio.hpp>
#include <opencv2/video/tracking.hpp>
#include <datacollection.h>

class videoPlayer : public QLabel
{
    Q_OBJECT

public:
    explicit videoPlayer(QWidget *parent = nullptr, dataCollection &col = *new dataCollection());
    void setPaintMode (bool mode);
    bool paintMode;
    int x;
    int y;
    int w;
    int h;

    cv::Mat frame;
    cv::Rect roi;

    void updateFrame (cv::Mat frame, int frameNo, bool track);
    void changeActive();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent (QMouseEvent *e) override;
    void mouseMoveEvent (QMouseEvent *e) override;
    void mouseReleaseEvent (QMouseEvent *e) override;

private:
    dataCollection* col;
    int currentFrameNo;
    bool mousePressed;

signals:
};

#endif // VIDEOPLAYER_H
