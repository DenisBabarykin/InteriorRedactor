#include "ZBuffer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------------------------

//Конструктор Z-буфера.

ZBuffer :: ZBuffer ( int ax, int ay ) : image(ax, ay)
{
    sX = ax; sY = ay;
    for ( int i = 0; i < sY; i++ )
    {
        //Выделение памяти под ячейки
        buff[i] = (double *) malloc ( sX * sizeof ( double ));
    }
}

//Деструктор Z-буфера.
ZBuffer :: ~ZBuffer ( )
{
    for ( int i = 0; i < sY; i++ )
        free( buff[i] ); //Освобождение памяти
}

//Функция, выводящая на экран содержимое заполненного Z-буфера.
void ZBuffer :: Show ()
{
    /*
    for ( int j = 0; j < sY; j++ )
        for ( int i = 0; i < sX; i++ )
            //Выводим пиксели на экран
            Form1->img->Canvas->Pixels[i][j] = (*( buff[j] + i )).color;/*clBlue(*( buff[ j ] + i )).color;*/
}

//Функция, 'очищающая' Z-буфер.
void ZBuffer :: Clear ()
{
    for ( int j = 0; j < sY; j++ )
        for ( int i = 0; i < sX; i++ )                                                               //-1 серый
            //Инициализируем ячейки Z-буфера
        {
            (*( buff[ j ] + i )).z = MAXDIST;
            //(*( buff[ j ] + i )).color = clWhite;
            image.fill(Qt::white);
        }
}

void ZBuffer :: PutTriangle (triangle& t)
{
    int ymax, ymin, ysc, e1, e;
    double x[3], y[3];
    double z_a[3];
    //Заносим x,y из t в массивы для последующей работы с ними
    x[0] = int( t.a->x ), y[0] = int( t.a->y );
    x[1] = int( t.b->x ), y[1] = int( t.b->y );
    x[2] = int( t.c->x ), y[2] = int( t.c->y );
    z_a[0] = t.a->z, z_a[1] = t.b->z, z_a[2] = t.c->z;
    //Определяем максимальный и минимальный y
    ymax = ymin = y[0];

    if ( ymax < y[1] )
        ymax = y[1];
    else
        if ( ymin > y[1] )
            ymin = y[1];
    if ( ymax < y[2] )
        ymax = y[2];
    else
        if ( ymin > y[2] )
            ymin = y[2];

    ymin = ( ymin < 0 ) ? 0 : ymin;
    ymax = ( ymax < sY ) ? ymax : sY;

    int ne;
    double x1, x2;
    int xsc1, xsc2;
    double z1, z2, tc, z;
    //Следующий участок кода перебирает все строки сцены
    //и определяет глубину каждого пикселя
    //для соответствующего треугольника
    for ( ysc = ymin; ysc < ymax; ysc++ )
    {
        ne = 0;
        for ( int e = 0; e < 3; e++ )
        {
            e1 = e + 1;
            if ( e1 == 3 )
                e1 = 0;

            if ( y[e] < y[e1] )
            {
                if ( y[e1] <= ysc || ysc < y[e] )
                    continue;
            }
            else
                if ( y[e] > y[e1] )
                {
                    if ( y[e1] > ysc || ysc >= y[e] )
                        continue;
                }
                else
                    continue;

            tc = double( y[e] - ysc ) / ( y[ e ] - y[ e1 ] );
            if ( ne )
            {
                x2 = x[ e ] +  ( tc * ( x[ e1 ] - x[ e ] ) );
                z2 = z_a[ e ] + tc * (z_a[ e1 ] - z_a[ e ]);
            }
            else
            {
                x1 = x[ e ] +  ( tc * ( x[ e1 ] - x[ e ] ) );
                z1 = z_a[ e ] + tc * (z_a[ e1 ] - z_a[ e ] );
                ne = 1;
            }
        }

        if ( x2 < x1 )
        {
            e = x1;
            x1 = x2;
            x2 = e;
            tc = z1;
            z1 = z2;
            z2 = tc;
        }

        xsc1 = ( x1 < 0 ) ? 0 : x1;
        xsc2 = ( x2 < sX ) ? x2 : sX;
        for ( int xsc = xsc1; xsc < xsc2; xsc++ )
        {
            tc = double( x1 - xsc ) / ( x1 - x2 );
            z = z1 + tc * ( z2 - z1 );
            //Если полученная глубина пиксела меньше той,
            //что находится в Z-Буфере - заменяем храняшуюся на новую.
            if ( z < (*( buff[ysc] + xsc )).z )
            {
                (*( buff[ ysc ] + xsc )).color = t.clr;
                (*( buff[ ysc ] + xsc )).z = z;
            }
        }
    }
}
