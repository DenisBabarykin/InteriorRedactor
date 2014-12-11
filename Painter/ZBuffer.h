#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "Painter.h"
#include "./Points/Points.h"

const int MAXDIST = -15000.0; //Максимальная глубина сцены было 500
const int MAXYLINES = 900; //Максимальное количество линий в сцене.   было  437

class triangle
{
public:
    Point3D a;
    Point3D b;
    Point3D c;
};

class ZBuffer : public Painter
{
public:
    double **buff;
    int sX, sY;	// Размер Z-Буфера

public:
    ZBuffer(int ax, int ay);
    ~ZBuffer();
    void PutTriangle(triangle &t, uint color);
    void Clear();
    void Paint(Scene &scene);
};



#endif // ZBUFFER_H
