#ifndef SKELETON_H
#define SKELETON_H

#include "Painter.h"

class Skeleton : public Painter
{
public:
    Skeleton(int height, int width, QObject *parent = 0);
    void Paint(Scene &scene);
    ~Skeleton();
};

#endif // SKELETON_H
