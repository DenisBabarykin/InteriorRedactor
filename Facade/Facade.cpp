#include "Facade.h"
#include <QtConcurrent/QtConcurrent>
#include "Painter/ZBuffer.h"
#include "Painter/Skeleton.h"

Facade::Facade(QObject *parent) :
    QObject(parent)
{
    painter = NULL;
    connect(&scene, SIGNAL(SceneActionDoneSignal()), this, SIGNAL(CommandDoneSignal()), Qt::QueuedConnection);
}

void Facade::CreateSceneCommand(SceneMetaData sceneMetaData)
{
    this->sceneMetaData = sceneMetaData;
    camera.Clear();
    scene.Clear();
    QtConcurrent::run(&scene, &Scene::LoadScene, &this->sceneMetaData);
}

void Facade::SaveSceneCommand(QString filename)
{
    sceneMetaData.SaveToFile(filename);
    emit CommandDoneSignal();
}

void Facade::RotateSceneCommand(int angleOX, int angleOY)
{
    if (!scene.IsEmpty())
        camera.AddRotation(angleOX, angleOY);
    emit CommandDoneSignal();
}

void Facade::ShiftSceneCommand(qreal dx, qreal dy, qreal dz)
{
    if (!scene.IsEmpty())
        camera.AddShift(dx, dy, (camera.GetDZ() > sceneMetaData.GetSceneLengthOZ() * 0.2 && dz > 0) ? (0) : (dz));
    emit CommandDoneSignal();
}

void Facade::DrawCommand()
{
    if (!scene.IsEmpty())
        QtConcurrent::run(this, &Facade::TransformAndDrawScene);
    else
        emit CommandDoneSignal();
}

void Facade::CreatePainterCommand(PainterType::PainterType painterType, int width, int height)
{
    if (painter)
        delete painter;

    switch(painterType)
    {
        case PainterType::zBuffer:
            painter = new ZBuffer(width, height);
            break;

        case PainterType::skeleton:
            painter = new Skeleton(width, height);
            break;

        default:
            throw "undefined painter type";
    }
    connect(painter, SIGNAL(PaintingDoneSignal(QImage*)), this, SIGNAL(DrawImageSignal(QImage*)), Qt::QueuedConnection);
    emit CommandDoneSignal();
}

void Facade::TransformAndDrawScene()
{
    scene.Rotate(camera.GetAngleOX(), camera.GetAngleOY());
    scene.Shift(camera.GetDX(), camera.GetDY(), -sceneMetaData.GetSceneLengthOZ() + camera.GetDZ());
    scene.Perspective();
    painter->Paint(scene);
    emit CommandDoneSignal();
}
