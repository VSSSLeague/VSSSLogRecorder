# Qt libs to import
QT += core    \
      network

# Project configs
TEMPLATE = app
DESTDIR  = ../bin
TARGET   = VSSSLogRecorder
VERSION  = 1.0.0

CONFIG += c++14 console
CONFIG -= app_bundle

# Temporary dirs
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/moc
RCC_DIR = tmp/rc

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += PROJECT_PATH=\\\"$${PWD}\\\"

# Project source files
SOURCES += \
        main.cpp \
        src/recorder/recorder.cpp \
        src/utils/exithandler/exithandler.cpp \
        src/utils/text/text.cpp \
        src/utils/timer/timer.cpp

# Project header files
HEADERS += \
    	src/recorder/recorder.h \
        src/utils/exithandler/exithandler.h \
        src/utils/text/text.h \
        src/utils/timer/timer.h \
        src/utils/types/messagetype/messagetype.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
