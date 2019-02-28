QT += testlib sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

#include(..\Modules\Modules.pri)

TEMPLATE = app

SOURCES += \  
    tst_testdatabase.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Modules/database/release/ -ldatabase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Modules/database/debug/ -ldatabase
else:unix: LIBS += -L$$OUT_PWD/../Modules/database/ -ldatabase

INCLUDEPATH += $$PWD/../Modules/database
DEPENDPATH += $$PWD/../Modules/database

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Modules/database/release/libdatabase.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Modules/database/debug/libdatabase.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Modules/database/release/database.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Modules/database/debug/database.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Modules/database/libdatabase.a
