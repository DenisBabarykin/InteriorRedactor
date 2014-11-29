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

    Point3D MaxPoint();
    Point3D MinPoint();

    void Shift(qreal dx, qreal dy, qreal dz);

public: //private:
    QVector<Point3D> vecPnts3D;
    QVector<FaceIndexes> vecIndx;
    void DrawModelFill(QPainter &painter);

private:
    void FillDataFromObjLoader(ObjLoader &objLoader);
    void Center();

};

#endif // OBJMODEL_H
