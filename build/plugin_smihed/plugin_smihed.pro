    message( "SMI HED plugin" )
    TEMPLATE = lib
    CONFIG += plugin no_plugin_name_prefix
    BINDIR  = "../../bin"
    win32::DESTDIR = "../bin"
    INCDIR  = "../../inc"
    SRCDIR  = "../../src"
    FRMDIR = "../../frm"
    RSCDIR = "../../media"
    LIBDIR = "../common"

    CONFIG += debug
    CONFIG(release, debug|release) {
        message( "Release" )
        TARGET = $$BINDIR/plug_SMIHED
        DEFINES += RELEASE_MODE
    }
    CONFIG(debug, debug|release) {
        message( "Debug" )
        TARGET = $$BINDIR/plug_SMIHED_d
        unix:QMAKE_CXXFLAGS += -g 
        DEFINES += DEBUG_MODE
    }

    OBJECTS_DIR = obj
    MOC_DIR = moc
    RCC_DIR = qrc
    UI_DIR = ui

    unix:QMAKE_CXXFLAGS += -std=c++11
    macx:INCLUDEPATH += /opt/local/include
    macx:LIBS += -L/opt/local/lib -lboost_regex-mt  -lm
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
    "$$INCDIR/SMIHED_widget.hpp" \
    "$$INCDIR/Plugin_widget.hpp" \
    "$$INCDIR/SMIHED.hpp" \
    "$$INCDIR/Timelinemarker.hpp"
    FORMS += \
    "$$FRMDIR/smihed.ui"
    SOURCES += \
    "$$SRCDIR/Plugin_widget.cpp"  \
    "$$SRCDIR/SMIHED_widget.cpp"  \
    "$$SRCDIR/SMIHED.cpp" \
    "$$SRCDIR/Timelinemarker.cpp"
    RESOURCES += \
    "$$RSCDIR/eyetracebutler.qrc"

