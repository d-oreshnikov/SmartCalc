QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    graph.cpp \
    qcustomplot.cpp \
    main.cpp \
    calcwindow.cpp \
    ../../backend/calculate/calculation.c \
    ../../backend/calculate/calc_help_func.c \
    ../../backend/parser/parser.c \
    ../../backend/parser/help_func.c \
    ../../backend/stack/stack.c \
    ../../backend/stack/calcstack/cstack.c

HEADERS += \
    graph.h \
    qcustomplot.h \
    calcwindow.h \
    ../../backend/calculate/calculation.h \
    ../../backend/calculate/calc_help_func.h \
    ../../backend/parser/parser.h \
    ../../backend/parser/help_func.h \
    ../../backend/stack/stack.h \
    ../../backend/stack/calcstack/cstack.h \

FORMS += \
    calcwindow.ui \
    graph.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
