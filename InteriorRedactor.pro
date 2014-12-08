#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T15:03:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InteriorRedactor
TEMPLATE = app

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += main.cpp\
        MainForm.cpp \
    LabelScene/LabelScene.cpp \
    ObjLoader/list.cpp \
    ObjLoader/obj_parser.cpp \
    ObjLoader/string_extra.cpp \
    ObjLoader/ObjLoader.cpp \
    Exception/Exception.cpp \
    Exception/UnknownCommandException.cpp \
    SceneRedactorForm.cpp \
    SceneSizesInput.cpp \
    SceneRedactorGraphics/GraphicsFurnitureItem.cpp \
    Scene/SceneMetaData.cpp \
    Scene/FigureMetaData.cpp \
    Points/Points.cpp \
    Scene/ObjModel.cpp \
    Exception/OpeningFileException.cpp \
    LabelScene/ZBuffer.cpp \
    Facade/Facade.cpp \
    Facade/SingletonFacade.cpp \
    Command/CommandController.cpp \
    Command/CommandRotate.cpp \
    Command/CommandCreateScene.cpp \
    Scene/Scene.cpp

HEADERS  += MainForm.h \
    LabelScene/LabelScene.h \
    ObjLoader/list.h \
    ObjLoader/obj_parser.h \
    ObjLoader/string_extra.h \
    ObjLoader/ObjLoader.h \
    Exception/Exception.h \
    Exception/UnknownCommandException.h \
    SceneRedactorForm.h \
    SceneSizesInput.h \
    SceneRedactorGraphics/GraphicsFurnitureItem.h \
    Scene/SceneMetaData.h \
    Scene/FigureMetaData.h \
    Points/Points.h \
    Scene/ObjModel.h \
    Exception/OpeningFileException.h \
    LabelScene/ZBuffer.h \
    Facade/Facade.h \
    Facade/SingletonFacade.h \
    Command/Command.h \
    Command/CommandController.h \
    Command/CommandRotate.h \
    Command/CommandCreateScene.h \
    Scene/Scene.h


FORMS    += MainForm.ui \
    SceneRedactorForm.ui \
    SceneSizesInput.ui

RESOURCES += \
    images.qrc
