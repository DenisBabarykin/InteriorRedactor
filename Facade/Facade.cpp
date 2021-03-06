#include "Facade.h"
#include <QtConcurrent/QtConcurrent>
#include "./Painter/SimpleZBuffer.h"
#include "./Painter/Skeleton.h"
#include "./Painter/ColorSimpleZBuffer.h"
#include "./Painter/SimpleLightZBuffer.h"
#include "./Painter/LightZBuffer.h"

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

void Facade::RotateSceneCommand(qreal angleOX, qreal angleOY)
{
    if (!scene.IsEmpty())
        camera.AddRotation(angleOX, angleOY);
    emit CommandDoneSignal();
}

void Facade::ShiftSceneCommand(qreal dx, qreal dy, qreal dz)
{
    if (!scene.IsEmpty())
        camera.AddShift(dx, dy, (camera.GetDZ() > sceneMetaData.GetSceneLengthOZ() * 0.1 && dz > 0) ? (0) : (dz));
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
        case PainterType::simpleZBuffer:
            painter = new SimpleZBuffer(width, height);
            break;

        case PainterType::skeleton:
            painter = new Skeleton(width, height);
            break;

        case PainterType::colorSimpleZBuffer:
            painter = new ColorSimpleZBuffer(width, height);
            break;

        case PainterType::simpleLightZBuffer:
            painter = new SimpleLightZBuffer(width, height);
            break;

        case PainterType::LightZBuffer:
            painter = new LightZBuffer(width, height);
            break;

        default:
            throw "undefined painter type";
    }
    connect(painter, SIGNAL(PaintingDoneSignal(QImage*)), this, SIGNAL(DrawImageSignal(QImage*)), Qt::QueuedConnection);
    emit CommandDoneSignal();
}

void Facade::TransformAndDrawScene()
{
    scene.Rotate(camera.GetAngleOX() + 10, camera.GetAngleOY() + 10);
    scene.Shift(camera.GetDX(), camera.GetDY(), -sceneMetaData.GetSceneLengthOZ() + camera.GetDZ());
    scene.Perspective();
    painter->Paint(scene);
    emit CommandDoneSignal();
}
