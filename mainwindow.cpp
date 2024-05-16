#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <direct.h>
#include <QFileDialog>
#include <QMessageBox>
#include <objectconf.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(this),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    col = *new dataCollection();
    col.setActiveItem("test");
    player = new videoPlayer(this, col);

    QVBoxLayout* layout =  qobject_cast<QVBoxLayout *>(ui->playerContainer->layout());
    layout->addWidget(qobject_cast<QLabel*>(player));
    layout->addStretch();

    currentFrameNo = 0;
    counter = 0;
    paintMode = false;

    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timeout () {
    currentFrameNo++;
    displayFrame(true);
}

void MainWindow::displayFrame (bool normalPlayback) {
    //qDebug() << this->ui->verticalLayout->geometry().width() << " " << this->ui->verticalLayout->geometry().height();
    player->setFrame(frame);
    player->updateFrame(currentFrameNo);
    if (currentFrameNo >= cap.get(cv::CAP_PROP_FRAME_COUNT)) {
        timer.stop();
        ui->pauseButton->setIcon(*new QIcon(":/icons/icons/play.svg"));
    } else {
        if (!normalPlayback) {
            cap.set(cv::CAP_PROP_POS_FRAMES, currentFrameNo);
        }
        ui->timeline->setValue(currentFrameNo);
        cap.read(frame);
        cv::resize(frame, frame, cv::Size(this->ui->verticalLayout->geometry().width(), this->ui->verticalLayout->geometry().height()));
        cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage dest((const uchar *)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

        player->setPixmap(QPixmap::fromImage(dest));
        ui->currentFrame->display(currentFrameNo);
    }
}

void MainWindow::on_pauseButton_clicked()
{
    if (!paintMode && cap.isOpened()) {
        if (timer.isActive()) {
            timer.stop();
            ui->pauseButton->setIcon(*new QIcon(":/icons/icons/play.svg"));
        } else {
            timer.start(1000 / cap.get(cv::CAP_PROP_FPS));
            ui->pauseButton->setIcon(*new QIcon(":/icons/icons/pause.svg"));
        }
    }
}


void MainWindow::on_prevButton_clicked()
{
    if (!timer.isActive() && currentFrameNo > 0 && cap.isOpened()) {
        currentFrameNo--;
        displayFrame(false);
        player->setFrame(frame);
        player->updateFrame(currentFrameNo);
    }
}


void MainWindow::on_nextButton_clicked()
{
    if (!timer.isActive() && currentFrameNo < cap.get(cv::CAP_PROP_FRAME_COUNT) - 1 && cap.isOpened()) {
        currentFrameNo++;
        displayFrame(false);
        player->setFrame(frame);
        player->updateFrame(currentFrameNo);
    }
}


void MainWindow::on_timeline_sliderMoved(int position)
{
    if (cap.isOpened()) {
        currentFrameNo = position;
        displayFrame(false);
        player->setFrame(frame);
        player->updateFrame(currentFrameNo);
    }
}


void MainWindow::on_paintButton_toggled(bool checked)
{
    if (cap.isOpened()) {
    if (checked) {
        timer.stop();
        ui->pauseButton->setIcon(*new QIcon(":/icons/icons/play.svg"));
        paintMode = true;
        player->setPaintMode(true);
        player->setFrame(frame);
    } else {
        paintMode = false;
        player->setPaintMode(false);
    }

    player->repaint();
    }
}

void MainWindow::on_openButton_clicked() {
    filename = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "video files (*.mp4 *.wmv *.avi *.mov *.3gp)");
    try {
    cap.open(filename.toStdString(), cv::CAP_ANY);
    if (cap.get(cv::CAP_PROP_FRAME_COUNT) > 0) {
        currentFrameNo = 0;
        paintMode = false;
        player->setPaintMode(false);
        ui->pauseButton->setIcon(*new QIcon(":/icons/icons/pause.svg"));

        timer.start(1000 / cap.get(cv::CAP_PROP_FPS));

        ui->totalFrames->display(cap.get(cv::CAP_PROP_FRAME_COUNT) - 1);
        ui->timeline->setMaximum(cap.get(cv::CAP_PROP_FRAME_COUNT) - 1);
    } else {
        QMessageBox mb;
        mb.critical(this, "File error", "File could not be read.");
    }
    } catch (cv::Exception e) {
        QMessageBox mb;
        mb.critical(this, "File error", "File could not be read.");
    }
}


void MainWindow::on_addButton_clicked()
{
    ui->selectionList->addItem(QString::number(counter));
    col.addItem(QString::number(counter));

    counter++;

    qDebug() << col.test();
}


void MainWindow::on_selectionList_itemDoubleClicked(QListWidgetItem *item)
{
    objectConf *conf = new objectConf(this, *this);
    conf->show();
    qDebug() << conf->getName();
}


void MainWindow::on_removeButton_clicked()
{
    if (ui->selectionList->currentItem() != NULL) {
        col.removeActiveItem();
        ui->selectionList->takeItem(ui->selectionList->currentRow());
        if (ui->selectionList->currentItem() != NULL) {
            col.setActiveItem(ui->selectionList->currentItem()->text());
            player->changeActive();
        }
    }
}

void MainWindow::on_selectionList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current != NULL) {
        col.setActiveItem(current->text());
        player->changeActive();
    }
}

dataCollection MainWindow::getcol () {
    return col;
}

void MainWindow::getConf (QString name, int start, int end) {
    qDebug() << col.test();
    trackedObject modified = col.getActiveItem();
    col.removeActiveItem();
    modified.setStart(start);
    modified.setEnd(end);
    col.setRect(modified);
}
