QT += core
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    channeltab.cpp \
    commchannel.cpp \
    k2602b.cpp \
    k2602b_channel.cpp \
    main.cpp \
    K2602bWindow.cpp

HEADERS += \
    K2602bWindow.h \
    channeltab.h \
    commchannel.h \
    k2602b.h \
    k2602b_channel.h

LIBS += \
    #-L"/usr/lib/x86_64-linux-gnu"
    -llxi

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
