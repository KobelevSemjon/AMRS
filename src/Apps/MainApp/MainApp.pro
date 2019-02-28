#-------------------------------------------------
#
# Project created by QtCreator 2018-12-19T13:04:33
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

include(..\..\..\opencv\opencv.pri)

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    miniview.cpp \
    algorithms.cpp \
    extendedtreeview.cpp \
    descriptiondialog.cpp \
    learningdialog.cpp \
    resultswindow.cpp \
    databasedialog.cpp

HEADERS += \
        mainwindow.h \
    miniview.h \
    imageview.h \
    algorithms.h \
    extendedtreeview.h \
    algorithms.h \
    descriptiondialog.h \
    learningdialog.h \
    resultswindow.h \
    databasedialog.h \
    wakeapp.h


FORMS += \
        mainwindow.ui \
    descriptiondialog.ui \
    learningdialog.ui \
    resultswindow.ui \
    databasedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
 #   clf_v0.sqlite

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Modules/database/release/ -ldatabase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Modules/database/debug/ -ldatabase
else:unix: LIBS += -L$$OUT_PWD/../../Modules/database/ -ldatabase

INCLUDEPATH += $$PWD/../../Modules/database
DEPENDPATH += $$PWD/../../Modules/database

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/database/release/libdatabase.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/database/debug/libdatabase.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/database/release/database.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/database/debug/database.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../Modules/database/libdatabase.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Modules/datatools/release/ -ldatatools
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Modules/datatools/debug/ -ldatatools
else:unix: LIBS += -L$$OUT_PWD/../../Modules/datatools/ -ldatatools

INCLUDEPATH += $$PWD/../../Modules/datatools
DEPENDPATH += $$PWD/../../Modules/datatools

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/datatools/release/libdatatools.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/datatools/debug/libdatatools.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/datatools/release/datatools.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/datatools/debug/datatools.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../Modules/datatools/libdatatools.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Modules/description/release/ -ldescription
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Modules/description/debug/ -ldescription
else:unix: LIBS += -L$$OUT_PWD/../../Modules/description/ -ldescription

INCLUDEPATH += $$PWD/../../Modules/description
DEPENDPATH += $$PWD/../../Modules/description

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/description/release/libdescription.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/description/debug/libdescription.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/description/release/description.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/description/debug/description.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../Modules/description/libdescription.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Modules/imaging/release/ -limaging
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Modules/imaging/debug/ -limaging
else:unix: LIBS += -L$$OUT_PWD/../../Modules/imaging/ -limaging

INCLUDEPATH += $$PWD/../../Modules/imaging
DEPENDPATH += $$PWD/../../Modules/imaging

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/imaging/release/libimaging.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/imaging/debug/libimaging.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/imaging/release/imaging.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/imaging/debug/imaging.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../Modules/imaging/libimaging.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Modules/machinelearning/release/ -lmachinelearning
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Modules/machinelearning/debug/ -lmachinelearning
else:unix: LIBS += -L$$OUT_PWD/../../Modules/machinelearning/ -lmachinelearning

INCLUDEPATH += $$PWD/../../Modules/machinelearning
DEPENDPATH += $$PWD/../../Modules/machinelearning

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/machinelearning/release/libmachinelearning.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/machinelearning/debug/libmachinelearning.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/machinelearning/release/machinelearning.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Modules/machinelearning/debug/machinelearning.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../Modules/machinelearning/libmachinelearning.a
