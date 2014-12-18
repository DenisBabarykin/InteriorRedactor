#ifndef SIMPLELIGHTZBUFFER_H
#define SIMPLELIGHTZBUFFER_H

#include "SimpleZBuffer.h"
#include "Polygon.h"

class SimpleLightZBuffer : public SimpleZBuffer
{
protected:
    void PutTriangle(Polygon &t, QColor color);
    static double GetCos(Point3D normal); // модуль косинуса угла между нормалью и вектором (0, 0, 1)

public:
    SimpleLightZBuffer(int ax, int ay, QObject *parent = 0);
    ~SimpleLightZBuffer();
    void Paint(Scene &scene);
};

#endif // SIMPLELIGHTZBUFFER_H
