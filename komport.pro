# -------------------------------------------------
# Project created by QtCreator 2011-02-09T06:45:33
# -------------------------------------------------
QT += core \
    widgets \
    gui
CONFIG+=debug
unix:QMAKE_CXXFLAGS_RELEASE += -g
unix:QMAKE_CFLAGS_RELEASE += -g
unix:QMAKE_CXXFLAGS_RELEASE -= -O2
unix:QMAKE_CFLAGS_RELEASE -= -O2
unix:QMAKE_LFLAGS_RELEASE = 
unix:target.path += /usr/bin
unix:INSTALLS += target
TARGET = komport
TEMPLATE = app
SOURCES += main.cpp \
    komport.cpp \
    cserial.cpp \
    cdevicelock.cpp \
    ccell.cpp \
    ccellarray.cpp \
    cscreen.cpp \
    cemulation.cpp \
    cemulationVT102.cpp \
    cemulationANSI.cpp \
    Win32Serial.cpp \
    cled.cpp
unix:SOURCES -= Win32Serial.cpp
HEADERS += komport.h \
    cserial.h \
    cdevicelock.h \
    ccell.h \
    ccellarray.h \
    cscreen.h \
    cemulation.h \
    cemulationVT102.h \
    cemulationANSI.h \
    Win32Serial.h \
    cled.h
unix:HEADERS -= Win32Serial.h
FORMS += komport.ui \
    settingsdialog.ui
RESOURCES += komport.qrc
OTHER_FILES += README.TXT \
    EMULATION.TXT
