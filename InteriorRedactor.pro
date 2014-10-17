#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T15:03:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InteriorRedactor
TEMPLATE = app


SOURCES += main.cpp\
        MainForm.cpp \
    LabelScene/LabelScene.cpp \
    ObjLoader/list.cpp \
    ObjLoader/obj_parser.cpp \
    ObjLoader/string_extra.cpp \
    ObjModel/ObjModel.cpp \
    ObjModel/Points.cpp \
    ObjLoader/ObjLoader.cpp \
    ObjModel/Camera.cpp \
    Exception/Exception.cpp \
    Exception/UnknownCommandException.cpp \
    SceneRedactorForm.cpp \
    ObjModel/FigureMetaData.cpp

HEADERS  += MainForm.h \
    LabelScene/LabelScene.h \
    ObjLoader/list.h \
    ObjLoader/obj_parser.h \
    ObjLoader/string_extra.h \
    ObjModel/ObjModel.h \
    ObjLoader/ObjLoader.h \
    ObjModel/Points.h \
    ObjModel/Camera.h \
    Exception/Exception.h \
    Exception/UnknownCommandException.h \
    SceneRedactorForm.h \
    ObjModel/FigureMetaData.h

FORMS    += MainForm.ui \
    SceneRedactorForm.ui
