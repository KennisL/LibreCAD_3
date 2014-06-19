#-------------------------------------------------
#
# Project created by QtCreator 2012-03-17T15:29:08
#
#------------------------------------------------

# Use common project definitions.
include(../settings.pri)

TARGET      = $$qtLibraryTarget(lcadviewerplugin)
TEMPLATE    = lib

VERSION=0.0.1

lessThan(QT_MAJOR_VERSION, 5) {
    QT += opengl
    CONFIG += designer plugin
} else {
    QT += opengl designer
    CONFIG += plugin
}

OTHER_FILES = CustomWidget.json
RESOURCES   = icons.qrc

win32 {
    #DESTDIR = ../lcdemo/
}
unix {
    macx {
        DESTDIR = ../demo.app/Contents/MacOS
	CONFIG(debug, debug|release) {
	    LIBS += -L$$DESTDIR -llckernel_debug
	} else {
	    LIBS += -L$$DESTDIR -llckernel
	}
        CONFIG+=link_pkgconfig
        PKGCONFIG+=cairo cairo-ft cairo-pdf cairo-png cairo-svg cairo-xcb cairo-xlib cairo-xlib-xcb cairo-xlib-xrender cairo-gl cairo-glx cairo-quartz pangocairo liblog4cxx
    } else {
        DESTDIR = ../lcdemo
	LIBS += -L$$DESTDIR -llckernel

        CONFIG+=link_pkgconfig
        PKGCONFIG+=cairo cairo-ft cairo-pdf cairo-png cairo-svg pangocairo liblog4cxx
    }
}

INCLUDEPATH += $$PWD/../lckernel
DEPENDPATH += $$PWD/../lckernel

HEADERS     =  \
    nano-signal-slot/nano_signal_slot.hpp \
    lcadviewerplugin.h \
    lcadviewer.h \
    drawitems/gradientbackground.h \
    const.h \
    drawitems/metricgrid.h \
    drawitems/cursor.h \
    helpers/snapmanager.h \
    helpers/snapmanagerimpl.h \
    events/snappointevent.h \
    events/drawevent.h \
    events/mousemoveevent.h \
    events/mousereleaseevent.h \
    events/selecteditemsevent.h \
    documentrenderer.h \
    lccairopainter.h \
    lcpainter.h \
    drawitems/lcvdrawitem.h \
    drawitems/lcvline.h \
    drawitems/lcvcircle.h \
    drawitems/endcaps.h \
    drawitems/lcdrawoptions.h \
    drawitems/lcvarc.h \
    drawitems/lcvellipse.h \
    drawitems/lcvtext.h \
    drawitems/lcvcoordinate.h \
    events/ui/uiarea.h \
    events/ui/uibase.h \
    events/ui/uiscene.h \
    events/ui/uievents.h \
    events/ui/uikeyboardevent.h \
    events/ui/uimousemoveevent.h \
    events/ui/uimouseevent.h

SOURCES     = lcadviewerplugin.cpp \
    lcadviewer.cpp \
    drawitems/gradientbackground.cpp \    
    drawitems/metricgrid.cpp \
    drawitems/cursor.cpp \
    helpers/snapmanagerimpl.cpp \
    documentrenderer.cpp \
    lccairopainter.cpp \
    drawitems/lcvdrawitem.cpp \
    drawitems/lcvline.cpp \
    drawitems/lcvcircle.cpp \
    drawitems/lcdrawoptions.cpp \
    drawitems/lcvarc.cpp \
    drawitems/lcvellipse.cpp \
    drawitems/lcvtext.cpp \
    drawitems/endcaps.cpp \
    drawitems/lcvcoordinate.cpp \
    events/ui/uiarea.cpp \
    events/ui/uibase.cpp \
    events/ui/uiscene.cpp \
    events/ui/uievents.cpp \
    events/ui/uikeyboardevent.cpp \
    events/ui/uimousemoveevent.cpp \
    events/ui/uimouseevent.cpp
