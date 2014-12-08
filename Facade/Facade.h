#ifndef FACADE_H
#define FACADE_H

#include <QObject>
#include "Scene/SceneMetaData.h"
#include "Scene/ObjModel.h"
#include "Scene/Scene.h"

class Facade : public QObject
{
    Q_OBJECT
public:
    explicit Facade(QObject *parent = 0);

    void CreateSceneCommand(SceneMetaData sceneMetaData);
    void SaveSceneCommand(QString filename);
    void RotateSceneCommand(int angleOX, int angleOY);
    void ShiftSceneCommand(qreal dx, qreal dy, qreal dz);

private:
    Scene scene;
    SceneMetaData sceneMetaData;

signals:
    void CommandDoneSignal();

public slots:

};

#endif // FACADE_H
