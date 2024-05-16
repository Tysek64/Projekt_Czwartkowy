#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QListWidgetItem>
#include <videoPlayer.h>
#include <dataCollection.h>
#include <opencv2/videoio.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer timer;
    videoPlayer *player;
    QString filename;
    QString savePath;

    cv::VideoCapture cap;
    cv::Mat frame;

    int currentFrameNo;
    bool paintMode;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    dataCollection getcol();
    void getConf (QString name, int start, int end, int labelClass, int labelType);

private:
    Ui::MainWindow *ui;
    dataCollection col;
    void displayFrame(bool normalPlayback);
    int counter;
    int videoWidth;
    int videoHeight;
    bool saveFile(cv::Mat image, cv::Rect roi, int frameNo, int labelClass, int labelType, QString dir, QString filename);

private slots:
    void on_timeout();
    void on_pauseButton_clicked();
    void on_prevButton_clicked();
    void on_nextButton_clicked();
    void on_timeline_sliderMoved(int position);
    void on_paintButton_toggled(bool checked);
    void on_openButton_clicked();
    void on_addButton_clicked();
    void on_selectionList_itemDoubleClicked(QListWidgetItem *item);
    void on_removeButton_clicked();
    void on_selectionList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_saveButton_clicked();
};
#endif // MAINWINDOW_H
