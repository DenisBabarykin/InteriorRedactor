#include "Facade.h"
#include <QtConcurrent/QtConcurrent>

Facade::Facade(QObject *parent) :
    QObject(parent)
{
    connect(&scene, SIGNAL(SceneActionDoneSignal()), this, SIGNAL(CommandDoneSignal()));
}

void Facade::CreateSceneCommand(SceneMetaData sceneMetaData)
{
    this->sceneMetaData = sceneMetaData;
    QtConcurrent::run(&scene, &Scene::LoadScene, &this->sceneMetaData);
}

void Facade::SaveSceneCommand(QString filename)
{
    sceneMetaData.SaveToFile(filename);
}

void Facade::RotateSceneCommand(int angleOX, int angleOY)
{
    QtConcurrent::run(&scene, &Scene::Rotate, angleOX, angleOY);
}

void Facade::ShiftSceneCommand(qreal dx, qreal dy, qreal dz)
{
    QtConcurrent::run(&scene, &Scene::Shift, dx, dy, dz);
}
