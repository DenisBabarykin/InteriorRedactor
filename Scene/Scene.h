#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include "./Figure/Figure.h"
#include "SceneMetaData.h"

class Painter;

class Scene : public QObject
{
    Q_OBJECT
private:
    friend class Painter;

    QList<Figure *> listFigOrig; // Оригинал
    QList<Figure *> listFigWork; // Рабочая копия

private:
    void ShiftPartly(int downBorder, int upBorder, qreal dx, qreal dy, qreal dz); // изменения включительно с границами
    void RotatePartly(int downBorder, int upBorder, qreal angleOX, qreal angleOY);
    void PerspectivePartly(int downBorder, int upBorder);

public:
    Scene();
    ~Scene();

    void LoadScene(SceneMetaData *sceneMetaData);
    void Clear();

    void Shift(qreal dx, qreal dy, qreal dz);
    void Rotate(qreal angleOX, qreal angleOY);
    void Perspective();

    bool IsEmpty();

signals:
    void SceneActionDoneSignal();

};

#endif // SCENE_H
