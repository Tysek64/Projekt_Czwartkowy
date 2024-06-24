#include "videoplayer.h"
#include <QPainter>
#include <QMouseEvent>

videoPlayer::videoPlayer(QWidget *parent, dataCollection &col)
    : QLabel{parent}
{
    paintMode = false;
    mousePressed = false;
    x = -1;
    y = -1;
    w = -1;
    h = -1;
    currentFrameNo = 0;

    roi = *new doubleRect(-1, -1, -1, -1);

    this->col = &col;
}


void videoPlayer::paintEvent (QPaintEvent *e) {
    QLabel::paintEvent(e);

    QPainter painter(this);

    painter.setBrush(QBrush(QColor(0, 200, 0, 100)));
    if (paintMode && x != -1 && y != -1 && w != -1 && h != -1) {
        if (!mousePressed) {
            for (int i = 0;i < col->getHSize();i++) {
                if (col->getObject(i).getRect(currentFrameNo).getW() > 0) {
                    doubleRect rect = col->getObject(i).getRect(currentFrameNo);
                    painter.drawRect(rect.getX(), rect.getY(), rect.getW(), rect.getH());
                }
            }
        } else {
            painter.drawRect(x, y, w, h);
        }
    }
            for (int i = 0;i < col->getHSize();i++) {
        if (col->getObject(i).getRect(currentFrameNo).getW() > 0) {
                    if (col->getObject(i).getRect(currentFrameNo).getW() > 0) {
                cv::Rect rect = doubleToCv(col->getObject(i).getRect(currentFrameNo), videoWidth, videoHeight);
                        painter.drawRect(rect.x, rect.y, rect.width, rect.height);
                }
    }
            }
    painter.setBrush(QBrush(QColor(255, 0, 0, 100)));
            cv::Rect rect = doubleToCv(col->getActiveItem().getRect(currentFrameNo), videoWidth, videoHeight);
    painter.drawRect(rect.x, rect.y, rect.width, rect.height);

    painter.end();
}

void videoPlayer::setPaintMode (bool mode) {
    paintMode = mode;
}

void videoPlayer::mousePressEvent (QMouseEvent *e) {
    if (paintMode) {
    this->x = e->pos().x();
    this->y = e->pos().y();

    this->w = -1;
    this->h = -1;

    this->repaint();

    mousePressed = true;
    }
}

void videoPlayer::mouseMoveEvent (QMouseEvent *e) {
    if (paintMode) {
    this->w = e->pos().x() - this->x;
    this->h = e->pos().y() - this->y;

    this->repaint();
    }
}

void videoPlayer::mouseReleaseEvent (QMouseEvent *e) {
    mousePressed = false;

    if (paintMode) {
    if (this->w < 0) {
        this->x += this->w;
        this->w *= -1;
    } else if (this->w == 0) {
        this->w = 1;
    }

    if (this->h < 0) {
        this->y += this->h;
        this->h *= -1;
    } else if (this->h == 0) {
        this->h = 1;
    }

    this->roi = *new doubleRect((double)x / videoWidth, (double)y / videoHeight, (double)w / videoWidth, (double)h / videoHeight);

    this->col->getActiveItem().addRect(currentFrameNo, roi, 1.0f, true);
    cv::Rect roiCV = doubleToCv(roi, frame.cols, frame.rows);
    this->col->getActiveItem().initTracker(frame, roiCV);

    repaint();
    }
}

void videoPlayer::updateFrame (cv::Mat frame, int frameNo, bool track) {
    if (track) {
    for (int i = 0;i < col->getHSize();i++) {
        roi = col->getObject(i).getRect(currentFrameNo);
        if (this->roi.getW() > 0 && this->roi.getH() > 0 && col->getObject(i).getRect(frameNo).getW() <= 0) {
    cv::Rect roiCV = doubleToCv(roi, frame.rows, frame.cols);
            float confidence = this->col->getObject(i).updateTracker(frame, roiCV);
    roi = *new doubleRect((double)roiCV.x / frame.cols, (double)roiCV.y / frame.rows, (double)roiCV.width / frame.cols, (double)roiCV.height / frame.rows);
        col->getObject(i).addRect(frameNo, roi, confidence, false);
    }
    }
    }

    this->frame = frame;
    currentFrameNo = frameNo;
}

void videoPlayer::changeActive () {
    repaint();
}

void videoPlayer::setDimensions (int w, int h) {
    videoWidth = w;
    videoHeight = h;
}

cv::Rect videoPlayer::doubleToCv (doubleRect rect, int w, int h) {
    return *new cv::Rect(rect.getX() * w, rect.getY() * h, rect.getW() * w, rect.getH() * h);
}
