QT += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core

CONFIG += c++17
INCLUDEPATH += inc/
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/CRC8.cpp \
    src/barometer.cpp \
    src/connect_window.cpp \
    src/dataframe.cpp \
    src/diagrams.cpp \
    src/digitalclock.cpp \
    src/main.cpp \
    src/mainqw.cpp \
    src/mainwindow.cpp \
    src/qcustomplot.cpp \
    src/thermometer.cpp

HEADERS += \
    inc/CRC8.h \
    inc/barometer.h \
    inc/connect_window.h \
    inc/dataframe.h \
    inc/diagrams.h \
    inc/digitalclock.h \
    inc/mainqw.h \
    inc/mainwindow.h \
    inc/qcustomplot.h \
    inc/thermometer.h

FORMS += \
    ui/connect_window.ui \
    ui/diagrams.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc

