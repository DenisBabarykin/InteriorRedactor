#ifndef POINTS_H
#define POINTS_H

#include <QPointF>

class Point3D
{
public:
    Point3D();
    Point3D(qreal x, qreal y, qreal z);

public:
    qreal x, y, z;

};

class Point2D
{
public:
    Point2D();
    Point2D(qreal x, qreal y);
    Point2D(Point3D point3D);

public:
    qreal x, y;

};

class FaceIndexes
{
public:
    FaceIndexes();
    FaceIndexes(int v1, int v2, int v3);

public:
    int v1, v2, v3;

};

#endif // POINTS_H
