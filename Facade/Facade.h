#ifndef FACADE_H
#define FACADE_H

#include <QObject>
#include "Scene/SceneMetaData.h"
#include "Scene/ObjModel.h"
#include "Scene/Scene.h"
#include "Scene/Camera.h"
#include "Painter/PainterType.h"

class Facade : public QObject
{
    Q_OBJECT
public:
    explicit Facade(QObject *parent = 0);

    void CreateSceneCommand(SceneMetaData sceneMetaData);
    void SaveSceneCommand(QString filename);
    void RotateSceneCommand(int angleOX, int angleOY);
    void ShiftSceneCommand(qreal dx, qreal dy, qreal dz);
    void DrawCommand();
    void CreatePainterCommand(PainterType painterType, int width, int height);

private:
    Scene scene;
    Camera camera;
    SceneMetaData sceneMetaData;
    Painter *painter;

private:
    void TransformAndDrawScene();

signals:
    void CommandDoneSignal();            // Текущая команда выполнена
    void DrawImageSignal(QImage *image); // Отрисовать передаваемый image

public slots:

};

#endif // FACADE_H
