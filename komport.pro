# -------------------------------------------------
# Project created by QtCreator 2011-02-09T06:45:33
# -------------------------------------------------
QT += core \
    gui
TARGET = komport
TEMPLATE = app
SOURCES += main.cpp \
    komport.cpp \
    cserial.cpp \
    cdevicelock.cpp \
    ccharcell.cpp \
    ccellarray.cpp \
    cscreen.cpp \
    cemulation.cpp \
    cemulationVT102.cpp \
    Win32Serial.cpp
unix:SOURCES -= Win32Serial.cpp
HEADERS += komport.h \
    cserial.h \
    cdevicelock.h \
    ccharcell.h \
    ccellarray.h \
    cscreen.h \
    cemulation.h \
    cemulationVT102.h \
    cemulationVT102.h \
    Win32Serial.h
unix:HEADERS -= Win32Serial.h
FORMS += komport.ui \
    settingsdialog.ui
RESOURCES += komport.qrc
OTHER_FILES += README.TXT
