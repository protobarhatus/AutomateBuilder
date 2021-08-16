#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T14:19:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++1z
CONFIG += c++1z
QMAKE_LFLAGS +=-std=c++1z
QMAKE_CXXFLAGS += -std=c++1z
TARGET = AutomatBuilder
TEMPLATE = app
QMAKE_CFLAGS_RELEASE = -O2 -MT
QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO += -O2 -MT -Zi
QMAKE_CFLAGS_DEBUG = -Zi -MTd
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
        startwindow.cpp \
    controller.cpp \
    data.cpp \
    automate.cpp \
    filework.cpp \
    createautomateform.cpp \
    algorithm.cpp \  
    action.cpp \
    actionelement.cpp \
    arithmeticaloperator.cpp \
    functionallowedrules.cpp \
    functionbannedrules.cpp \
    functioncell.cpp \
    functionchance.cpp \
    functioncondinr.cpp \
    functioncount.cpp \
    functionrand.cpp \
    functionstep.cpp \
    logicelement.cpp \
    logicoperator.cpp \
    logicvalue.cpp \
    logicvalueoperator.cpp \
    logicvariable.cpp \
    rule.cpp \
    statement.cpp \
    value.cpp \
    valueelement.cpp \
    valuevariable.cpp \
    addvariableform.cpp \
    addvariableformcontroller.cpp \
    somedataworks.cpp \
    field.cpp \
    cell.cpp \
    parser.cpp \
    functiontern.cpp \
    functionnot.cpp \
    mydeleter.cpp \
    functioncurrentcell.cpp \
    addstatementform.cpp \
    addstatementformcontroller.cpp \
    addruleform.cpp \
    actionsetstatement.cpp \
    actionsetbyf.cpp \
    actionban.cpp \
    actionallow.cpp \
    specialoperators.cpp \
    addruleformcontroller.cpp \
    addenvironsfunctionform.cpp \
    addenvironsfunctionformcontroller.cpp \
    simulatingform.cpp \
    simulatingpropetries.cpp \
    simulatingpropetriesform.cpp \
    drawingfield.cpp \
    statementscounter.cpp \
    wavefunction.cpp \
    functionslcount.cpp \
    thread.cpp \
    variablesvaluecontainer.cpp \
    simulationpropetriesform.cpp \
    simulationpropetries.cpp \
    simulator.cpp \
    fileparser.cpp \
    fielddistributor.cpp \
    choosefielddialog.cpp \
    configuration.cpp \
    countersamount.cpp \
    aboutprogrammform.cpp

HEADERS += \
        startwindow.h \
    controller.h \
    data.h \
    algorithm.h \
    automate.h \
    filework.h \
    createautomateform.h \
    algorithm.h \
    automate.h \
    controller.h \
    createautomateform.h \
    data.h \
    filework.h \
    startwindow.h \
    algorithm.h \
    automate.h \
    controller.h \
    createautomateform.h \
    data.h \
    filework.h \
    startwindow.h \
    action.h \
    actionelement.h \
    algorithm.h \
    arithmeticaloperator.h \
    automate.h \
    controller.h \
    createautomateform.h \
    data.h \
    filework.h \
    functionallowedrules.h \
    functionbannedrules.h \
    functioncell.h \
    functionchance.h \
    functioncondinr.h \
    functioncount.h \
    functionrand.h \
    functionstep.h \
    logicelement.h \
    logicoperator.h \
    logicvalue.h \
    logicvalueoperator.h \
    logicvariable.h \
    rule.h \
    startwindow.h \
    statement.h \
    value.h \
    valueelement.h \
    valuevariable.h \
    addvariableform.h \
    addvariableformcontroller.h \
    somedataworks.h \
    field.h \
    cell.h \
    parser.h \
    functiontern.h \
    functionnot.h \
    mydeleter.h \
    functioncurrentcell.h \
    addstatementform.h \
    addstatementformcontroller.h \
    addruleform.h \
    actionsetstatement.h \
    actionsetbyf.h \
    actionban.h \
    actionallow.h \
    specialoperators.h \
    addruleformcontroller.h \
    addenvironsfunctionform.h \
    addenvironsfunctionformcontroller.h \
    simulatingform.h \
    simulatingpropetries.h \
    simulatingpropetriesform.h \
    drawingfield.h \
    statementscounter.h \
    wavefunction.h \
    functionslcount.h \
    thread.h \
    variablesvaluecontainer.h \
    simulationpropetriesform.h \
    simulationpropetries.h \
    simulator.h \
    fileparser.h \
    fielddistributor.h \
    choosefielddialog.h \
    configuration.h \
    countersamount.h \
    aboutprogrammform.h

FORMS += \
        startwindow.ui \
    createautomateform.ui \
    addvariableform.ui \
    addstatementform.ui \
    addruleform.ui \
    addenvironsfunctionform.ui \
    simulatingform.ui \
    simulatingpropetriesform.ui \
    simulationpropetriesform.ui \
    choosefielddialog.ui \
    aboutprogrammform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

STATECHARTS += \
    common diagramm.scxml

DISTFILES += \
    common.qmodel \
    start_form_model.qmodel \
    algorithm_description.qmodel

RESOURCES += \
    resources.qrc
