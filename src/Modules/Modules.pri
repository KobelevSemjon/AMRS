include(..\..\opencv\opencv.pri)

#SRC_PATH = $$dirname(PWD)               #путь до папки AMRS/src
#PROJECT_PATH = $$dirname(SRC_PATH)      #путь до папки AMRS
#BIN_PATH = $$PROJECT_PATH/bin           #путь для сборки AMRS/bin (настройки сборки AMRS\bin\debug и AMRS\bin\release)
#RELEASE_PATH = $$BIN_PATH/release       #путь для debug-версии
#DEBUG_PATH = $$BIN_PATH/debug           #путь для релиз-версии

#INCLUDEPATH += $$SRC_PATH\Modules\datatools
#DEPENDPATH += $$SRC_PATH\Modules\datatools
#debug: LIBS += -L$$DEBUG_PATH\Modules\datatools\debug -ldatatools
#release: LIBS += -L$$RELEASE_PATH\Modules\datatools\release -ldatatools

#INCLUDEPATH += $$SRC_PATH\Modules\description
#DEPENDPATH += $$SRC_PATH\Modules\description
#debug: LIBS += -L$$DEBUG_PATH\Modules\description\debug -ldescription
#release: LIBS += -L$$RELEASE_PATH\Modules\description\release -ldescription

#INCLUDEPATH += $$SRC_PATH\Modules\imaging
#DEPENDPATH += $$SRC_PATH\Modules\imaging
#debug: LIBS += -L$$DEBUG_PATH\Modules\imaging\debug -limaging
#release: LIBS += -L$$RELEASE_PATH\Modules\imaging\release -limaging

#INCLUDEPATH += $$SRC_PATH\Modules\machinelearning
#DEPENDPATH += $$SRC_PATH\Modules\machinelearning
#debug: LIBS += -L$$DEBUG_PATH\Modules\machinelearning\debug -lmachinelearning
#release: LIBS += -L$$RELEASE_PATH\Modules\machinelearning\release -lmachinelearning

#QT += sql
#INCLUDEPATH += $$SRC_PATH\Modules\database
#DEPENDPATH += $$SRC_PATH\Modules\database
#debug: LIBS += -L$$DEBUG_PATH\Modules\database\debug -ldatabase
#release: LIBS += -L$$RELEASE_PATH\Modules\database\release -ldatabase
