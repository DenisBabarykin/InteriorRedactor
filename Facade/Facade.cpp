#include "Facade.h"
#include <QtConcurrent/QtConcurrent>

Facade::Facade(QObject *parent) :
    QObject(parent)
{
    painter = NULL;
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
        camera.AddShift(dx, dy, dz);
    emit CommandDoneSignal();
}

void Facade::DrawCommand()
{
    if (!scene.IsEmpty())
        QtConcurrent::run(this, &Facade::TransformAndDrawScene);
    else
        emit CommandDoneSignal();
}

void Facade::CreatePainterCommand(PainterType painterType, int width, int height)
{
    if (painter)
        delete painter;

    switch(painterType)
    {
        case zBuffer:
            painter = new ZBuffer(width, height);
            connect(painter, SIGNAL(PaintingDoneSignal(QImage*)), this, SIGNAL(DrawImageSignal(QImage*)));
            break;

        case skeleton:
            // инстанцирование каркасным рисовальщиком
            connect(painter, SIGNAL(PaintingDoneSignal(QImage*)), this, SIGNAL(DrawImageSignal(QImage*)));
            break;

        default:
            throw "undefined painter type";
    }
    emit CommandDoneSignal();
}

void Facade::TransformAndDrawScene()
{
    scene.Rotate(camera.GetAngleOX(), camera.GetAngleOY());
    scene.Shift(camera.GetDX(), camera.GetDY(), camera.GetDZ());
    scene.Perspective();
    painter->Paint(scene);
    emit CommandDoneSignal();
}
