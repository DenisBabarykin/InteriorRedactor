#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include "./Figure/Figure.h"
#include "SceneMetaData.h"
#include "./Painter/Surface.h"
#include <vector>

using namespace std;

class Painter;

class Scene : public QObject
{
    Q_OBJECT
private:
    friend class Painter;

    QList<Figure *> listFigOrig; // Оригинал
    QList<Figure *> listFigWork; // Рабочая копия

    vector<Surface> surfaces;
    vector<ObjVector> vertices;
    vector<ObjVector> originalVertices;
    vector<ObjVector> normals;
    vector<ObjVector> originalNormals;
    vector<ObjMaterial> materials;

private:
    void ShiftPartly(int downBorder, int upBorder, qreal dx, qreal dy, qreal dz); // изменения включительно с границами
    void RotatePartly(int downBorder, int upBorder, qreal angleOX, qreal angleOY);
    void PerspectivePartly(int downBorder, int upBorder);

    void ContainersFill();

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
