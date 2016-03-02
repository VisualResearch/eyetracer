TEMPLATE = subdirs
CONFIG += static
SUBDIRS = common eyetracebutler plugin_smired5 plugin_smihed plugin_idmt
eyetracebutler.depends = common
plugin_smired5.depends = common
plugin_smihed.depends = common
plugin_idmt.depends = common


unix:!macx:message( "Linux" )
win32:message( "Win" )
macx:message( "Mac Osx" )
