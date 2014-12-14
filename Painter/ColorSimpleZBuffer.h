#ifndef COLORSIMPLEZBUFFER_H
#define COLORSIMPLEZBUFFER_H

#include "Painter.h"
#include "./Points/Points.h"
#include "SimpleZBuffer.h"

class ColorSimpleZBuffer : public SimpleZBuffer
{
public:
    ColorSimpleZBuffer(int ax, int ay, QObject *parent = 0);
    ~ColorSimpleZBuffer();
    void Paint(Scene &scene);
};

#endif // COLORSIMPLEZBUFFER_H
