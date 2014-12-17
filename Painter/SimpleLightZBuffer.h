#ifndef SIMPLELIGHTZBUFFER_H
#define SIMPLELIGHTZBUFFER_H

#include "SimpleZBuffer.h"
#include "Polygon.h"

class SimpleLightZBuffer : public SimpleZBuffer
{
private:
    bool wasUnfront;

public:
    SimpleLightZBuffer(int ax, int ay, QObject *parent = 0);
    ~SimpleLightZBuffer();
    void Paint(Scene &scene);
    void PutTriangle(Polygon &t, QColor color);
    inline bool isFront(Polygon &tr, ObjVector *normal);
    static double GetCos(Point3D normal); // модуль косинуса угла между нормалью и вектором (0, 0, 1)
};

#endif // SIMPLELIGHTZBUFFER_H
