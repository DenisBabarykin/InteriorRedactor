#ifndef COLORSIMPLEZBUFFER_H
#define COLORSIMPLEZBUFFER_H

#include "Painter.h"
#include "./Points/Points.h"
#include "SimpleZBuffer.h"

class ColorSimpleZBuffer : public SimpleZBuffer
{
protected:
    inline bool isFarthest(triangle &tr);
    inline bool isFront(triangle &tr, ObjVector *normal);

public:
    ColorSimpleZBuffer(int ax, int ay, QObject *parent = 0);
    ~ColorSimpleZBuffer();
    void Paint(Scene &scene);

};

#endif // COLORSIMPLEZBUFFER_H
