#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <QImage>
#include "./Points/Points.h"

#define MAXDIST -15000.0 //Максимальная глубина сцены было 500
#define MAXYLINES 900 //Максимальное количество линий в сцене.   было  437

class triangle
{
public:
    Point3D a;
    Point3D b;
    Point3D c;
};

class ZBuffer
{
public:
    double **buff;
    QImage image;
    int sX, sY;	// Размер Z-Буфера

public:
    ZBuffer(int ax, int ay);
    ~ZBuffer();
    void PutTriangle(triangle &t, uint color);
    void Clear();
};



#endif // ZBUFFER_H
