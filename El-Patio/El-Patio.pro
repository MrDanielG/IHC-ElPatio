#-------------------------------------------------
#
# Project created by QtCreator 2020-01-21T09:38:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = El-Patio
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

SOURCES += \
        almacenista/almacenista_crear_insumo.cpp \
        almacenista/almacenista_menu.cpp \
        catalogomesas.cpp \
        main.cpp \
        mainwindow.cpp \
        mesero/mesero_agregar_extra.cpp \
        mesero/mesero_editar_platillo.cpp \
        mesero/mesero_menu_comandas.cpp \
        mesero/mesero_tarjeta_chica.cpp \
        mesero/mesero_tarjeta_menu.cpp \
        mesero/mesero_tarjeta_transferir.cpp \
        mesero/mesero_transferir_platillo.cpp \
        models/platillo.cpp

HEADERS += \
        almacenista/almacenista_crear_insumo.h \
        almacenista/almacenista_menu.h \
        catalogomesas.h \
        mainwindow.h \
        mesero/mesero_agregar_extra.h \
        mesero/mesero_editar_platillo.h \
        mesero/mesero_menu_comandas.h \
        mesero/mesero_tarjeta_chica.h \
        mesero/mesero_tarjeta_menu.h \
        mesero/mesero_tarjeta_transferir.h \
        mesero/mesero_transferir_platillo.h \
        models/platillo.h

FORMS += \
        almacenista/almacenista_crear_insumo.ui \
        almacenista/almacenista_menu.ui \
        catalogomesas.ui \
        mainwindow.ui \
        mesero/mesero_agregar_extra.ui \
        mesero/mesero_editar_platillo.ui \
        mesero/mesero_menu_comandas.ui \
        mesero/mesero_tarjeta_chica.ui \
        mesero/mesero_tarjeta_menu.ui \
        mesero/mesero_tarjeta_transferir.ui \
        mesero/mesero_transferir_platillo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc

DISTFILES +=
