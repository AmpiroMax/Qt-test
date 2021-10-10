QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(release, debug|release): LIBS += -L$$PWD/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release):   LIBS += -L$$PWD/SFML/lib/ -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += $$PWD/SFML/include/
DEPENDPATH +=  $$PWD/SFML/include/

SOURCES += \
    GlobalWidget/globalwidget.cpp \
    SFMLWidget/sfmlwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GlobalWidget/globalwidget.h \
    SFMLWidget/sfmlwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
