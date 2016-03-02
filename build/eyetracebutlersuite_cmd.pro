    message( "BUTLER command line" )
    unix:!macx:message( "Linux" )
    TEMPLATE = app
    BINDIR  = "../bin"
    win32::DESTDIR = "../bin"
    INCDIR  = "../inc"
    SRCDIR  = "../src"
    LIBDIR = "common"

    DEFINES += CONSOLE_MODE
    macx:CONFIG -=app_bundle
    CONFIG += debug
    CONFIG += static
    CONFIG(release, debug|release) {
        message( "Release" )
        TARGET = $$BINDIR/eyetracebutler_cmd
        DEFINES += RELEASE_MODE
    }
    CONFIG(debug, debug|release) {
        message( "Debug" )
        TARGET = $$BINDIR/eyetracebutler_cmd_d
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
    LIBS += -L$$LIBDIR

    DEPENDPATH += \
        "$$SRCDIR" \
        "$$INCDIR"
    INCLUDEPATH += \
        "$$INCDIR" \
        "$$LIBDIR"

    # Input
    HEADERS += \
    "$$INCDIR/Data.hpp" \
    "$$INCDIR/LogFileWriter.hpp" \
    "$$INCDIR/Plugin.hpp" \
    "$$INCDIR/Quality.hpp" \
    "$$INCDIR/Subject.hpp" \
    "$$INCDIR/common.hpp" \
    "$$INCDIR/SMIRED5.hpp" \
    "$$INCDIR/SMIHED.hpp" \
    "$$INCDIR/IDMT.hpp"
    SOURCES +=\
    "$$SRCDIR/Eyetracebutler_cmd.cpp" \
    "$$SRCDIR/Data.cpp"\
    "$$SRCDIR/Plugin.cpp"\
    "$$SRCDIR/Quality.cpp" \
    "$$SRCDIR/Subject.cpp" \
    "$$SRCDIR/common.cpp" \
    "$$SRCDIR/SMIRED5.cpp" \
    "$$SRCDIR/SMIHED.cpp" \
    "$$SRCDIR/IDMT.cpp"

