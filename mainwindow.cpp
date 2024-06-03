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
#include <QJsonObject>
#include <QJsonDocument>
#include <objectconf.h>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(this),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    col = *new dataCollection();
    col.setActiveName("test");
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
    if (currentFrameNo >= cap.get(cv::CAP_PROP_FRAME_COUNT)) {
        timer.stop();
        ui->pauseButton->setIcon(*new QIcon(":/icons/icons/play.svg"));
    } else {
        if (!normalPlayback) {
            cap.set(cv::CAP_PROP_POS_FRAMES, currentFrameNo);
        }
        ui->timeline->setValue(currentFrameNo);
        cap.read(frame);
        cv::resize(frame, frame, cv::Size(videoWidth, videoHeight));
        cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage dest((const uchar *)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

        player->setPixmap(QPixmap::fromImage(dest));
        ui->currentFrame->display(currentFrameNo);
    }
    player->updateFrame(frame, currentFrameNo, true);
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
        //player->updateFrame(frame, currentFrameNo, true);
    }
}


void MainWindow::on_nextButton_clicked()
{
    if (!timer.isActive() && currentFrameNo < cap.get(cv::CAP_PROP_FRAME_COUNT) - 1 && cap.isOpened()) {
        currentFrameNo++;
        displayFrame(false);
        //player->updateFrame(frame, currentFrameNo, true);
    }
}


void MainWindow::on_timeline_sliderMoved(int position)
{
    if (cap.isOpened()) {
        currentFrameNo = position;
        displayFrame(false);
        player->updateFrame(frame, currentFrameNo, true);
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
        player->updateFrame(frame, currentFrameNo, false);
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
        videoWidth = this->ui->playerContainer->geometry().width();
        videoHeight = this->ui->playerContainer->geometry().height();
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
}


void MainWindow::on_selectionList_itemDoubleClicked(QListWidgetItem *item)
{
    objectConf *conf = new objectConf(this, *this, col.getActiveItem(), cap.get(cv::CAP_PROP_FRAME_COUNT));
    conf->show();
}

void MainWindow::on_removeButton_clicked()
{
    if (ui->selectionList->currentItem() != NULL) {
        col.removeActiveItem(true);
        ui->selectionList->takeItem(ui->selectionList->currentRow());
        if (ui->selectionList->currentItem() != NULL) {
            col.setActiveName(ui->selectionList->currentItem()->text());
            player->changeActive();
        }
    }
}

void MainWindow::on_selectionList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current != NULL) {
        col.setActiveName(current->text());
        player->changeActive();
    }
}

dataCollection MainWindow::getcol () {
    return col;
}

void MainWindow::getConf (QString name, int start, int end, int labelClass, int labelType) {
    trackedObject modified = col.getActiveItem();
    col.removeActiveItem(false);
    modified.setStart(start);
    modified.setEnd(end);
    modified.setClass(labelClass);
    modified.setType(labelType);
    col.setRect(modified);
}

void MainWindow::on_saveButton_clicked()
{
    savePath = QFileDialog::getExistingDirectory(this, "Choose save folder", QDir::homePath());
    for (int i = 0;i < col.getSize();i++) {
        cap.set(cv::CAP_PROP_POS_FRAMES, col.getFrameNo(i));
        cv::Mat trackedFrame;
        cap.read(trackedFrame);
        cvtColor(trackedFrame, trackedFrame, cv::COLOR_BGR2RGB);
        cv::Rect roi = col.getImage(i);
        if (roi.x + roi.width > videoWidth) {
            roi = *new cv::Rect(roi.x, roi.y, videoWidth - roi.x, roi.height);
        }

        if (roi.y + roi.height > videoHeight) {
            roi = *new cv::Rect(roi.x, roi.y, roi.width, videoHeight - roi.y);
        }

        if (roi.x < 0) {
            roi = *new cv::Rect(0, roi.y, roi.width + roi.x, roi.height);
        }

        if (roi.y < 0) {
            roi = *new cv::Rect(roi.x, 0, roi.width, roi.height + roi.y);
        }

        float hScale = (float)trackedFrame.cols / (float)videoWidth;
        float vScale = (float)trackedFrame.rows / (float)videoHeight;

        roi = *new cv::Rect((int)(hScale * (float)roi.x), (int)(vScale * (float)roi.y), (int)(hScale * (float)roi.width), (int)(vScale * (float)roi.height));

        if (!saveFile(trackedFrame, roi, col.getConfidence(i), col.getFrameNo(i), col.getItem(i).getClass(), col.getItem(i).getType(), savePath, QFileInfo(filename).baseName())) {
            QMessageBox mb;
            mb.critical(this, "Save error", "Error saving file");
        }
    }

    QMessageBox mb;
    mb.information(this, "Save complete", "Finished saving files");
}

    bool MainWindow::saveFile(cv::Mat image, cv::Rect roi, float confidence, int frameNo, int labelClass, int labelType, QString dir, QString filename)
{
    QString savedFilename = dir + "/" + filename
                            + "_" + QString::number( frameNo )
                            + "_" + QString::number( roi.x )
                            + "_" + QString::number( roi.y )
                            + "_" + QString::number( roi.x + roi.width )
                            + "_" + QString::number( roi.y + roi.height )
                            + "_" + QString::number( labelType )
                            + "_" + QString::number( labelClass ) + ".png";
    QFile savedImage = QFile(savedFilename);
    if (savedImage.open(QIODevice::WriteOnly))
    {
        cv::Mat croppedImage = image(roi);
        QImage dest((const uchar *)croppedImage.data, croppedImage.cols, croppedImage.rows, croppedImage.step, QImage::Format_RGB888);
        (QPixmap::fromImage(dest)).save(savedFilename);

        QString savedFilenameJSON = savedFilename;
        savedFilenameJSON.replace(QObject::tr(".png"),QObject::tr(".json"));

        QFile savedJSON = QFile(savedFilenameJSON);

        QJsonObject regionMetadata;
        regionMetadata.insert("x1", roi.x);
        regionMetadata.insert("y1", roi.y);
        regionMetadata.insert("x2", roi.x + roi.width);
        regionMetadata.insert("y2", roi.y + roi.height);

        QJsonObject imageMetadata;
        imageMetadata.insert("file_source", filename);
        imageMetadata.insert("framenumber", frameNo);
        imageMetadata.insert("region", regionMetadata);
        imageMetadata.insert("confidence", confidence);
        imageMetadata.insert("label_type", labelType);
        imageMetadata.insert("label_class", labelClass);
        imageMetadata.insert("file_image", QFileInfo(savedFilename).baseName());

        QJsonDocument jsonToSave;
        jsonToSave.setObject(imageMetadata);

        if(savedJSON.open(QIODevice::WriteOnly))
        {
            savedJSON.write(jsonToSave.toJson());
            savedJSON.close();
        }

    }
    else
    {
        return false;
    }

    return true;
}

void MainWindow::on_eraseButton_clicked()
{
    col.getActiveItem().removeRect(currentFrameNo);
    player->changeActive();
}


void MainWindow::on_startButton_clicked()
{
    trackedObject current = col.getActiveItem();
    current.setStart(currentFrameNo);
    col.setActiveIten(current);
}


void MainWindow::on_endButton_clicked()
{
    trackedObject current = col.getActiveItem();
    current.setEnd(currentFrameNo);
    col.setActiveIten(current);
}

