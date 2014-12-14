#ifndef SIMPLEZBUFFER_H
#define SIMPLEZBUFFER_H

#include "Painter.h"
#include "./Points/Points.h"

const int MAXDIST = -31000.0; //Максимальная глубина сцены

class triangle
{
public:
    Point3D a;
    Point3D b;
    Point3D c;
};

class SimpleZBuffer : public Painter
{
public:
    double **buff;
    int sX, sY;	// Размер Z-Буфера

public:
    SimpleZBuffer(int ax, int ay, QObject *parent = 0);
    ~SimpleZBuffer();
    void PutTriangle(triangle &t, uint color);
    void Clear();
    void Paint(Scene &scene);
};



#endif // SIMPLEZBUFFER_H
