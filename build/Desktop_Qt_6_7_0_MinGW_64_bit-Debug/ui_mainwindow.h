/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLCDNumber *totalFrames;
    QLCDNumber *currentFrame;
    QPushButton *pauseButton;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QSlider *timeline;
    QPushButton *paintButton;
    QWidget *playerContainer;
    QVBoxLayout *verticalLayout;
    QPushButton *openButton;
    QListWidget *selectionList;
    QPushButton *addButton;
    QPushButton *removeButton;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(600, 400));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        totalFrames = new QLCDNumber(centralwidget);
        totalFrames->setObjectName("totalFrames");
        totalFrames->setGeometry(QRect(10, 40, 64, 23));
        currentFrame = new QLCDNumber(centralwidget);
        currentFrame->setObjectName("currentFrame");
        currentFrame->setGeometry(QRect(10, 10, 64, 23));
        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setGeometry(QRect(110, 10, 21, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/play.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton->setIcon(icon);
        prevButton = new QPushButton(centralwidget);
        prevButton->setObjectName("prevButton");
        prevButton->setGeometry(QRect(80, 10, 21, 24));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/prev.svg"), QSize(), QIcon::Normal, QIcon::Off);
        prevButton->setIcon(icon1);
        nextButton = new QPushButton(centralwidget);
        nextButton->setObjectName("nextButton");
        nextButton->setGeometry(QRect(140, 10, 21, 24));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/next.svg"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon2);
        timeline = new QSlider(centralwidget);
        timeline->setObjectName("timeline");
        timeline->setGeometry(QRect(170, 10, 531, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(timeline->sizePolicy().hasHeightForWidth());
        timeline->setSizePolicy(sizePolicy1);
        timeline->setOrientation(Qt::Horizontal);
        paintButton = new QPushButton(centralwidget);
        paintButton->setObjectName("paintButton");
        paintButton->setGeometry(QRect(710, 10, 21, 24));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/paint.svg"), QSize(), QIcon::Normal, QIcon::Off);
        paintButton->setIcon(icon3);
        paintButton->setCheckable(true);
        playerContainer = new QWidget(centralwidget);
        playerContainer->setObjectName("playerContainer");
        playerContainer->setGeometry(QRect(10, 70, 691, 501));
        sizePolicy.setHeightForWidth(playerContainer->sizePolicy().hasHeightForWidth());
        playerContainer->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(playerContainer);
        verticalLayout->setObjectName("verticalLayout");
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName("openButton");
        openButton->setGeometry(QRect(80, 40, 21, 24));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/open.svg"), QSize(), QIcon::Normal, QIcon::Off);
        openButton->setIcon(icon4);
        selectionList = new QListWidget(centralwidget);
        selectionList->setObjectName("selectionList");
        selectionList->setGeometry(QRect(710, 40, 81, 531));
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(740, 10, 21, 24));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/add.svg"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon5);
        removeButton = new QPushButton(centralwidget);
        removeButton->setObjectName("removeButton");
        removeButton->setGeometry(QRect(770, 10, 21, 24));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/remove.svg"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon6);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pauseButton->setText(QString());
        prevButton->setText(QString());
        nextButton->setText(QString());
        paintButton->setText(QString());
        openButton->setText(QString());
        addButton->setText(QString());
        removeButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
