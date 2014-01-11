#-------------------------------------------------
#
# Project created by QtCreator 2014-01-11T01:04:03
#
#-------------------------------------------------

QT       -= gui

TARGET = QGoogleAuthenticator
TEMPLATE = lib

DEFINES += QGOOGLEAUTHENTICATOR_LIBRARY

SOURCES += qgoogleauthenticator.cpp \
    hmac.cpp \
    base32.cpp

HEADERS += qgoogleauthenticator.h\
        qgoogleauthenticator_global.h \
    hmac.h \
    base32.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
