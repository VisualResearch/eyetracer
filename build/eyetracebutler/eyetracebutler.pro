    message( "BUTLER" )
    TEMPLATE = app
    BINDIR  = "../../bin"
    win32::DESTDIR = "../bin"
    INCDIR  = "../../inc"
    SRCDIR  = "../../src"
    FRMDIR = "../../frm"
    RSCDIR = "../../media"
    LIBDIR = "../common"

    macx:CONFIG -=app_bundle
    CONFIG += debug
    CONFIG(release, debug|release) {
        message( "Release" )
        TARGET = $$BINDIR/eyetracebutler
        DEFINES += RELEASE_MODE
    }
    CONFIG(debug, debug|release) {
        message( "Debug" )
        TARGET = $$BINDIR/eyetracebutler_d
        unix:QMAKE_CXXFLAGS += -g
        DEFINES += DEBUG_MODE
    }

    OBJECTS_DIR = obj
    MOC_DIR = moc
    RCC_DIR = qrc
    UI_DIR = ui

    unix:QMAKE_CXXFLAGS += -std=c++11
    macx:INCLUDEPATH += /opt/local/include
    macx:LIBS += -L/opt/local/lib -lboost_regex-mt -lm
    unix:!macx:LIBS += -lboost_regex
    LIBS += -L$$LIBDIR -lcommon

    DEPENDPATH += \
        "$$SRCDIR" \
        "$$INCDIR" \
        "$$RSCDIR"
    INCLUDEPATH += \
        "$$INCDIR" \
        "$$LIBDIR"

    # Input
    HEADERS += \
    "$$INCDIR/Eyetracebutler_widget.hpp" \
    "$$INCDIR/Plugin_widget.hpp"
    FORMS += \
    "$$FRMDIR/eyetracebutler.ui"
    SOURCES +=\
    "$$SRCDIR/Eyetracebutler_widget.cpp"
    RESOURCES += \
    "$$RSCDIR/eyetracebutler.qrc"
