#include "Points.h"

Point3D::Point3D()
{
    x = y = z = 0;
}

Point3D::Point3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point2D::Point2D()
{
    x = y = 0;
}

Point2D::Point2D(double x, double y)
{
    this->x = x;
    this->y = y;
}

Point2D::Point2D(Point3D point3D)
{
    x = point3D.x;
    y = point3D.y;
}

FaceIndexes::FaceIndexes()
{
    v1 = v2 = v3 = 0;
}

FaceIndexes::FaceIndexes(int v1, int v2, int v3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}
