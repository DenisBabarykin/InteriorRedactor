#ifndef POINTS_H
#define POINTS_H

class Point3D
{
public:
    Point3D();
    Point3D(double x, double y, double z);

public:
    double x, y, z;

};

class Point2D
{
public:
    Point2D();
    Point2D(double x, double y);
    Point2D(Point3D point3D);

public:
    double x, y;

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
