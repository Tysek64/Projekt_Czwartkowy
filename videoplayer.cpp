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

    roi = *new cv::Rect(-1, -1, -1, -1);

    this->col = &col;
}


void videoPlayer::paintEvent (QPaintEvent *e) {
    QLabel::paintEvent(e);

    QPainter painter(this);

    painter.setBrush(QBrush(QColor(255, 0, 0, 100)));
    if (paintMode && x != -1 && y != -1 && w != -1 && h != -1) {
        if (!mousePressed && col->getActiveItem().getRect(currentFrameNo).width > 0) {
            cv::Rect rect = col->getActiveItem().getRect(currentFrameNo);
            painter.drawRect(rect.x, rect.y, rect.width, rect.height);
        } else {
            painter.drawRect(x, y, w, h);
        }
    }
    if (col->getActiveItem().getRect(currentFrameNo).width > 0) {
        cv::Rect rect = col->getActiveItem().getRect(currentFrameNo);
            painter.drawRect(rect.x, rect.y, rect.width, rect.height);
        }

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
    }

    if (this->h < 0) {
        this->y += this->h;
        this->h *= -1;
    }

    this->roi = *new cv::Rect(x, y, w, h);

    this->col->getActiveItem().addRect(currentFrameNo, roi, true);

    tracker = cv::TrackerNano::create();
    tracker->init(frame, roi);

    repaint();
    }
}

void videoPlayer::setFrame (cv::Mat frame) {
    this->frame = frame;
}

void videoPlayer::updateFrame (int frame) {
    roi = col->getActiveItem().getRect(currentFrameNo);
    if (this->roi.width > 0 && this->roi.height > 0) {
        this->tracker->update(this->frame, roi);

        col->getActiveItem().addRect(frame, roi, false);
    }

    currentFrameNo = frame;
}

void videoPlayer::changeActive () {
    repaint();
}
