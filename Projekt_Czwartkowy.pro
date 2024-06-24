QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

OPENCV_DIR += "$$PWD/OpenCV/release"

INCLUDEPATH += "$${OPENCV_DIR}/install/include"

#INCLUDEPATH += /../

CVLIBS += "$${OPENCV_DIR}/bin/libopencv_core490.dll"
CVLIBS += "$${OPENCV_DIR}/bin/libopencv_highgui490.dll"
CVLIBS += "$${OPENCV_DIR}/bin/libopencv_imgcodecs490.dll"
CVLIBS += "$${OPENCV_DIR}/bin/libopencv_imgproc490.dll"
CVLIBS += "$${OPENCV_DIR}/bin/libopencv_calib3d490.dll"
CVLIBS += "$${OPENCV_DIR}/bin/libopencv_video490.dll"
CVLIBS += "$${OPENCV_DIR}/bin/libopencv_videoio490.dll"

LIBS += $$CVLIBS

SOURCES += \
    datacollection.cpp \
    doublerect.cpp \
    main.cpp \
    mainwindow.cpp \
    objectconf.cpp \
    trackedobject.cpp \
    videoplayer.cpp

HEADERS += \
    datacollection.h \
    doublerect.h \
    mainwindow.h \
    objectconf.h \
    trackedobject.h \
    videoplayer.h

FORMS += \
    mainwindow.ui \
    objectconf.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
