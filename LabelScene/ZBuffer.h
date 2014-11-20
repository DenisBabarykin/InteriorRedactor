#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <QImage>

#define MAXDIST 15000.0 //Максимальная глубина сцены было 500
#define MAXYLINES 900 //Максимальное количество линий в сцене.   было  437
typedef struct Cell CELL;
//Структура ячейки, из которых будет состоять Z-буфер.
struct Cell
{
    double z;
    int color;
};

class ZBuffer
{
public:
    double *buff[ MAXYLINES ];
    QImage image;
    int sX, sY;	// Размер Z-Буфера
    ZBuffer ( int, int );
    ~ZBuffer ();
    void PutTriangle ( triangle& );
    void Show ();
    void Clear ();
};

#endif // ZBUFFER_H
