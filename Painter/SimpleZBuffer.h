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
protected:
    qreal **buff;
    int sX, sY;	// Размер Z-Буфера
    void PutTriangle(triangle &t, uint color);

public:
    SimpleZBuffer(int ax, int ay, QObject *parent = 0);
    virtual ~SimpleZBuffer();
    void Clear();
    void Paint(Scene &scene);
};



#endif // SIMPLEZBUFFER_H
