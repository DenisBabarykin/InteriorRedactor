#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <QImage>
#include "./Points/Points.h"

#define MAXDIST 15000.0 //Максимальная глубина сцены было 500
#define MAXYLINES 900 //Максимальное количество линий в сцене.   было  437
typedef struct Cell CELL;
//Структура ячейки, из которых будет состоять Z-буфер.
struct Cell
{
    double z;
    int color;
};

class triangle
{
public:
    Point3D a;
    Point3D b;
    Point3D c;
};

class ZBuffer
{
public:
    double *buff[ MAXYLINES ];
    QImage image;
    int sX, sY;	// Размер Z-Буфера
    ZBuffer ( int, int );
    ~ZBuffer ();
    void PutTriangle(triangle &t, uint color);
    void Show ();
    void Clear ();
};



#endif // ZBUFFER_H
