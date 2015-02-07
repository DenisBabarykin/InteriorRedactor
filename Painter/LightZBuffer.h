#ifndef LIGHTZBUFFER_H
#define LIGHTZBUFFER_H

#include "SimpleLightZBuffer.h"

class LightZBuffer : public SimpleLightZBuffer
{
protected:
    inline bool isFront(Polygon &tr, ObjVector *normal);
    inline bool isFarthest(Polygon &tr);

public:
    LightZBuffer(int ax, int ay, QObject *parent = 0);
    ~LightZBuffer();
    void Paint(Scene &scene);
};

#endif // LIGHTZBUFFER_H
