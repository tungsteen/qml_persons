TEMPLATE = app
QT += qml quick widgets sql
CONFIG += c++14

INCLUDEPATH += 3rdparty

SOURCES += \
    src/main.cpp \
    src/repository.cpp \
    src/person.cpp \
    src/sortfilterproxymodel.cpp \
    src/model.cpp \
    3rdparty/ModelTest/modeltest.cpp

HEADERS += \
    src/repository.h \
    src/person.h \
    src/model.h \
    src/sortfilterproxymodel.h \
    3rdparty/ModelTest/modeltest.h

RESOURCES += \
    qml/qml.qrc \
    icons/icons.qrc \
    fonts/fonts.qrc \
    data/data.qrc
