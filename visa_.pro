#-------------------------------------------------
#
# Project created by QtCreator 2019-11-08T12:46:50
#
#-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
QT += widgets
TEMPLATE = app
TARGET = visa_
TEMPLATE = app

#INCLUDEPATH += ../../../../Program Files/IVI Foundation/VISA/Win64/Include/
#INCLUDEPATH += C:\Program Files\IVI Foundation\VISA\Win64\Include\
#LIBS += C:\Program Files\IVI Foundation\VISA\Win64\Lib_x64\msc\

INCLUDEPATH += ../../../../Program Files/IVI Foundation/VISA/Win64/Include/
INCLUDEPATH += "C:/Program Files/IVI Foundation/VISA/Win64/Include"
LIBS += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc/visa32.lib"


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ./instrument/basedevice.cpp \
    ./instrument/osc.cpp \
    ./component/base.cpp \
    ./component/testcomp.cpp \
    ./component/vdd_test.cpp \
    ./component/init.cpp \
    component/ibase.cpp \
    ./factory/factory.cpp \
    ./factory/singleton.cpp \
    ./factory/registerclass.cpp \
    runner.cpp \
    ui/treeitem.cpp \
    ui/treemodel.cpp \
    ui/mydelegate.cpp \
    device/qadb.cpp \
    component/baseadb.cpp \
    component/devices.cpp



HEADERS += \
        mainwindow.h \
    ./instrument/basedevice.h \
    ./instrument/osc.h \
    ./component/base.h \
    ./component/testcomp.h \
    ./component/vdd_test.h \
    ./component/init.h \
    component/ibase.h \
    ./factory/factory.h \
    ./factory/singleton.h \
    ./factory/registerclass.h \
    runner.h \
    ui/treeitem.h \
    ui/treemodel.h \
    ui/mydelegate.h \
    3rdparty/rapidjson/error/en.h \
    3rdparty/rapidjson/error/error.h \
    3rdparty/rapidjson/internal/biginteger.h \
    3rdparty/rapidjson/internal/clzll.h \
    3rdparty/rapidjson/internal/diyfp.h \
    3rdparty/rapidjson/internal/dtoa.h \
    3rdparty/rapidjson/internal/ieee754.h \
    3rdparty/rapidjson/internal/itoa.h \
    3rdparty/rapidjson/internal/meta.h \
    3rdparty/rapidjson/internal/pow10.h \
    3rdparty/rapidjson/internal/regex.h \
    3rdparty/rapidjson/internal/stack.h \
    3rdparty/rapidjson/internal/strfunc.h \
    3rdparty/rapidjson/internal/strtod.h \
    3rdparty/rapidjson/internal/swap.h \
    3rdparty/rapidjson/msinttypes/inttypes.h \
    3rdparty/rapidjson/msinttypes/stdint.h \
    3rdparty/rapidjson/allocators.h \
    3rdparty/rapidjson/cursorstreamwrapper.h \
    3rdparty/rapidjson/document.h \
    3rdparty/rapidjson/encodedstream.h \
    3rdparty/rapidjson/encodings.h \
    3rdparty/rapidjson/filereadstream.h \
    3rdparty/rapidjson/filewritestream.h \
    3rdparty/rapidjson/fwd.h \
    3rdparty/rapidjson/istreamwrapper.h \
    3rdparty/rapidjson/memorybuffer.h \
    3rdparty/rapidjson/memorystream.h \
    3rdparty/rapidjson/ostreamwrapper.h \
    3rdparty/rapidjson/pointer.h \
    3rdparty/rapidjson/prettywriter.h \
    3rdparty/rapidjson/rapidjson.h \
    3rdparty/rapidjson/reader.h \
    3rdparty/rapidjson/schema.h \
    3rdparty/rapidjson/stream.h \
    3rdparty/rapidjson/stringbuffer.h \
    3rdparty/rapidjson/writer.h \
    device/qadb.h \
    component/baseadb.h \
    component/devices.h


FORMS += \
        mainwindow.ui





win32:CONFIG(release, debug|release): LIBS += -L'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/' -lvisa64
else:win32:CONFIG(debug, debug|release): LIBS += -L'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/' -lvisa64
else:unix: LIBS += -L'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/' -lvisa64

INCLUDEPATH += 'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc'
DEPENDPATH += 'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc'

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += 'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/visa64.lib'
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += 'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/visa64.lib'
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += 'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/visa64.lib'
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += 'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/visa64.lib'
else:unix: PRE_TARGETDEPS += 'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/libvisa64.a'
