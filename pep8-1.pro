# #####################################################################
# Automatically generated by qmake (2.01a) Mon Apr 13 22:35:17 2009
# #####################################################################
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Help system support for html files
QT += webkit

# Input
HEADERS += mainwindow.h \
    sourcecodepane.h \
    objectcodepane.h \
    cpupane.h \
    assemblerlistingpane.h \
    memorytracepane.h \
    memorydumppane.h \
    inputpane.h \
    outputpane.h \
    terminalpane.h \
    redefinemnemonicsdialog.h \
    pep.h \
    byteconverterhex.h \
    byteconverterdec.h \
    byteconverterchar.h \
    byteconverterbin.h \
    pep.h \
    helpdialog.h
FORMS += mainwindow.ui \
    sourcecodepane.ui \
    objectcodepane.ui \
    cpupane.ui \
    assemblerlistingpane.ui \
    memorytracepane.ui \
    memorydumppane.ui \
    inputpane.ui \
    outputpane.ui \
    terminalpane.ui \
    redefinemnemonicsdialog.ui \
    byteconverterhex.ui \
    byteconverterdec.ui \
    byteconverterchar.ui \
    byteconverterbin.ui \
    helpdialog.ui
SOURCES += main.cpp \
    mainwindow.cpp \
    sourcecodepane.cpp \
    objectcodepane.cpp \
    cpupane.cpp \
    assemblerlistingpane.cpp \
    memorytracepane.cpp \
    memorydumppane.cpp \
    inputpane.cpp \
    outputpane.cpp \
    terminalpane.cpp \
    redefinemnemonicsdialog.cpp \
    byteconverterhex.cpp \
    byteconverterdec.cpp \
    byteconverterchar.cpp \
    byteconverterbin.cpp \
    pep.cpp \
    helpdialog.cpp
OTHER_FILES += images/update.png \
    images/undo.png \
    images/ShowMemoryPane.png \
    images/save.png \
    images/RESET2edit.png \
    images/RESET2.XPM \
    images/redo.png \
    images/query.png \
    images/print.png \
    images/paste.png \
    images/open.png \
    images/new.png \
    images/MEMORY.XPM \
    images/LOAD.png \
    images/EXPAND.XPM \
    images/EXECUTE.XPM \
    images/EXECUTE.png \
    images/DefaultView.png \
    images/cut.png \
    images/copy.png \
    images/config.png \
    images/CodeOnly.xpm \
    images/CodeMemory.xpm \
    images/CodeCPUMemory.xpm \
    images/CodeCPU.xpm \
    images/CodeCPU.png \
    images/assembler.xpm \
    images/assembler.png
RESOURCES += pep8resources.qrc \
    helpresources.qrc
