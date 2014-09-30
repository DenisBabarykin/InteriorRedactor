#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "ObjLoader/ObjLoader.h"
#include "Points.h"
#include <QVector>
#include <QPainter>

class ObjModel
{
public:
    explicit ObjModel(ObjLoader &objLoader);

    void DrawModel(QPainter &painter);
    void RotateOX(double angle);
    void RotateOY(double angle);

private:
    QVector<Point3D> vecPnts3D;
    QVector<FaceIndexes> vecIndx;

private:
    void FillDataFromObjLoader(ObjLoader &objLoader);
    void Center();
    Point3D MaxPoint();
    Point3D MinPoint();

};

#endif // OBJMODEL_H
