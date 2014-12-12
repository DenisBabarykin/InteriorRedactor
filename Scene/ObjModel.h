#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "ObjLoader/ObjLoader.h"
#include "./Points/Points.h"
#include <QVector>
#include <QPainter>

class ObjModel
{
public:
    ObjModel();
    explicit ObjModel(ObjLoader &objLoader);

    void DrawModel(QPainter &painter);
    void RotateOX(double angle);
    void RotateOY(double angle);
    void Rotate(const ObjModel *baseModel, qreal angleOX, qreal angleOY);
    void Perspective(const ObjModel *baseModel);

    Point3D MaxPoint();
    Point3D MinPoint();

    void Shift(const ObjModel *baseModel, qreal dx, qreal dy, qreal dz); // Сдвиг относительно базовой модели

public: //private:
    std::vector<Point3D> vecPnts3D;
    std::vector<FaceIndexes> vecIndx;
    void DrawModelFill(QPainter &painter);

private:
    void FillDataFromObjLoader(ObjLoader &objLoader);
    void Center();

};

#endif // OBJMODEL_H
