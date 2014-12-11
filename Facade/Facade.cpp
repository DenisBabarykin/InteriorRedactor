#include "Facade.h"
#include <QtConcurrent/QtConcurrent>

Facade::Facade(QObject *parent) :
    QObject(parent)
{
    //connect(&scene, SIGNAL(SceneActionDoneSignal()), this, SIGNAL(CommandDoneSignal()));
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
    camera.AddRotation(angleOX, angleOY);
}

void Facade::ShiftSceneCommand(qreal dx, qreal dy, qreal dz)
{
    camera.AddShift(dx, dy, dz);
}

void Facade::DrawCommand()
{
    QtConcurrent::run(&scene, &Scene::Rotate, camera.GetAngleOX(), camera.GetAngleOY());
    QtConcurrent::run(&scene, &Scene::Shift, camera.GetDX(), camera.GetDY(), camera.GetDZ());
    // вызов рисовальщика
}
