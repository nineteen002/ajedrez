QT       += core gui
QT       += network
LIBS += -lws2_32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bishop.cpp \
    boardblock.cpp \
    chessboard.cpp \
    chesspiece.cpp \
    king.cpp \
    knight.cpp \
    loby.cpp \
    main.cpp \
    packages.cpp \
    pawn.cpp \
    queen.cpp \
    rook.cpp \
    socket.cpp

HEADERS += \
    bishop.h \
    boardblock.h \
    chessboard.h \
    chesspiece.h \
    king.h \
    knight.h \
    loby.h \
    packages.h \
    pawn.h \
    queen.h \
    rook.h \
    socket.h

FORMS += \
    loby.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images_rsc.qrc
