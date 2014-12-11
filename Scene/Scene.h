#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include "ObjModel.h"
#include "SceneMetaData.h"
#include <vector>

class Painter;

class Scene : public QObject
{
    Q_OBJECT
private:
    friend class Painter;

    std::vector<ObjModel *> listFigOrig; // Оригинал
    std::vector<ObjModel *> listFigWork; // Рабочая копия

private:
    void ShiftPartly(int downBorder, int upBorder, qreal dx, qreal dy, qreal dz); // изменения включительно с границами
    void RotatePartly(int downBorder, int upBorder, int angleOX, int angleOY);

public:
    Scene();
    ~Scene();

    void LoadScene(const SceneMetaData *sceneMetaData);
    void Clear();

    void Shift(qreal dx, qreal dy, qreal dz);
    void Rotate(int angleOX, int angleOY);

signals:
    void SceneActionDoneSignal();

};

#endif // SCENE_H
