    message( "COMMON LIBRARY" )
    TEMPLATE = lib
    CONFIG += staticlib
    DESTDIR  = "./"
    INCDIR  = "../../inc"
    SRCDIR  = "../../src"
    FRMDIR = "../../frm"
    RSCDIR = "../../media"

    CONFIG += debug
    CONFIG(release, debug|release) {
        message( "Release" )
        DEFINES += RELEASE_MODE
    }
    CONFIG(debug, debug|release) {
        message( "Debug" )
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
        "$$INCDIR"

    # Input
    HEADERS += \
    "$$INCDIR/Data.hpp" \
    "$$INCDIR/LogFileWriter.hpp" \
    "$$INCDIR/Plugin.hpp" \
    "$$INCDIR/Quality.hpp" \
    "$$INCDIR/Subject.hpp" \
    "$$INCDIR/common.hpp"

    SOURCES +=\
    "$$SRCDIR/Data.cpp"\
    "$$SRCDIR/Plugin.cpp"\
    "$$SRCDIR/Quality.cpp" \
    "$$SRCDIR/Subject.cpp" \
    "$$SRCDIR/common.cpp"
    RESOURCES += \
    "$$RSCDIR/eyetracebutler.qrc"
