
QT       += core gui sql
TARGET = QtKinectExample
TEMPLATE = app

CONFIG +=  qtestlib

HEADERS += QtKinectExample.h \
    QtKinect_global.h \
    QtKinect.h \
    callBacks.h \
    database/browser.h \
    database/connectionwidget.h \
    guiitem.h \
    robot.h

SOURCES += QtKinectExample.cpp main.cpp \
    QtKinect.cpp \
    database/connectionwidget.cpp \
    database/browser.cpp \
    guiitem.cpp \
    robot.cpp

FORMS    += QtKinectExample.ui \
    database/browserwidget.ui

FREENECTPATH = "/home/barry963/libfreenect"

INCLUDEPATH +=  /home/barry963/Kinect/NITE_Bin_Dev_Linux/Include/ \
                $$FREENECTPATH/include/ \
                /home/barry963/Kinect/OpenNI_unstable/Include

LIBS += -L$$FREENECTPATH/build/lib/ -lfreenect \
        -L/usr/lib -lOpenNI \
        -lXnDeviceSensorV2KM -lXnCore -lXnFormats -lXnDDK \
        -lXnVNite_1_5_2


OTHER_FILES += \
    configTracking.xml

RESOURCES += \
    res.qrc
