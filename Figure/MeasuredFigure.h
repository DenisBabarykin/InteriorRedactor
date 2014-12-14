#ifndef MEASUREDFIGURE_H
#define MEASUREDFIGURE_H

#include "./Points/Points.h"

class MeasuredFigure
{
public:
    virtual Point3D MaxPoint() = 0;
    virtual Point3D MinPoint() = 0;
};

#endif // MEASUREDFIGURE_H
