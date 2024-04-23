QT += quick sql widgets


CONFIG += qmltypes
QML_IMPORT_NAME = io.chronos.backend
QML_IMPORT_MAJOR_VERSION = 1.0

SOURCES += \
        backend.cpp \
        data/event.cpp \
        data/task.cpp \
        db/dbmanager.cpp \
        db/eventsmanager.cpp \
        db/tasksmanager.cpp \
        main.cpp \
        utils.cpp

resources.files = main.qml TaskForm.qml TaskList.qml TimerForm.qml
resources.prefix = /$${TARGET}
RESOURCES += resources \
    icons.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    backend.h \
    data/event.h \
    data/task.h \
    db/dbmanager.h \
    db/eventsmanager.h \
    db/tasksmanager.h \
    utils.h
