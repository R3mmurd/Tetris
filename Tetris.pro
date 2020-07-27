QMAKE_CXX = clang++

QT += core widgets multimedia

CONFIG += c++14

HEADERS += \
    piece.H \
    defs.H \
    board.H \
    allpieces.H \
    boardcanvas.H \
    tetriscanvas.H

SOURCES += \
    piece.C \
    defs.C \
    main.C \
    board.C \
    allpieces.C \
    boardcanvas.C \
    tetriscanvas.C

RESOURCES += \
    multimedia.qrc
