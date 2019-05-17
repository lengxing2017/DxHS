QT += quick
QT += serialport sql xml printsupport
CONFIG += c++11

CONFIG += "lang-en_GB lang-zh_CN"

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    module/imagecapture.cpp \
    module/imageanalysis.cpp \
    module/lismgr.cpp \
    module/sequence.cpp \
    module/exglobal.cpp \
    module/sqlitemgr.cpp \
    module/dao/assaymgr.cpp \
    module/dao/logmgr.cpp \
    module/dao/panelmgr.cpp \
    module/dao/paneltestmgr.cpp \
    module/dao/parmmgr.cpp \
    module/dao/testresultmgr.cpp \
    module/dao/usermgr.cpp \
    module/printermgr.cpp \
    module/uart/commgr.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    module/imagecapture.h \
    module/imageanalysis.h \
    module/lismgr.h \
    module/sequence.h \
    module/exglobal.h \
    module/entity/Assay.h \
    module/entity/AssayItem.h \
    module/entity/Log.h \
    module/entity/Panel.h \
    module/entity/PanelTest.h \
    module/entity/Param.h \
    module/entity/TestResult.h \
    module/entity/User.h \
    module/sqlitemgr.h \
    module/dao/assaymgr.h \
    module/dao/assaymgr.h \
    module/dao/logmgr.h \
    module/dao/panelmgr.h \
    module/dao/paneltestmgr.h \
    module/dao/parmmgr.h \
    module/dao/testresultmgr.h \
    module/dao/usermgr.h \
    module/printermgr.h \
    module/uart/ihandle.h \
    module/uart/commgr.h \
    module/uart/frame.h \
    module/uart/framebuffer.h \
    module/uart/framestatus.h \
    module/dao/AssayMgr.h

DISTFILES +=
