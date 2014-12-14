#include "SimpleZBuffer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>


SimpleZBuffer::SimpleZBuffer(int ax, int ay, QObject *parent) : Painter(ax, ay, parent)
{
    sX = ax; sY = ay;
    buff = NULL;
    if (!(buff = (double **) malloc(sX * sizeof(double))))
        throw "Memory alloc error";
    for ( int i = 0; i < sX; i++ )
        if (!(buff[i] = (double *) malloc(sY * sizeof(double))))
            throw "Memory alloc error";;
    Clear();
}

SimpleZBuffer::~SimpleZBuffer()
{
    for (int i = 0; i < sX; i++)
        free(buff[i]);
    free(buff);
    buff = NULL;
}

void SimpleZBuffer::Clear()
{
    for (int i = 0; i < sX; i++)
        for (int j = 0; j < sY; j++)
            buff[i][j] = MAXDIST;

    currentFrame->fill(Qt::black); // !!!
}

void SimpleZBuffer::Paint(Scene &scene)
{
    Clear();
    QStringList listColors = QColor::colorNames();
    for (int i = 0; i < GetListFig(scene)->size() - 1; ++i) // GetListFig(scene)->size() - 1, чтобы не рисовать стены
    {
        for (int j = 0; j < (*GetListFig(scene))[i]->faceCount; ++j)
        {
            triangle tr;

            tr.a = Point3D((*GetListFig(scene))[i]->vertexList[ (*GetListFig(scene))[i]->faceList[j]->vertex_index[0] ]->e[0],
                    (*GetListFig(scene))[i]->vertexList[ (*GetListFig(scene))[i]->faceList[j]->vertex_index[0] ]->e[1],
                    (*GetListFig(scene))[i]->vertexList[ (*GetListFig(scene))[i]->faceList[j]->vertex_index[0] ]->e[2]);

            tr.b = Point3D((*GetListFig(scene))[i]->vertexList[ (*GetListFig(scene))[i]->faceList[j]->vertex_index[1] ]->e[0],
                    (*GetListFig(scene))[i]->vertexList[ (*GetListFig(scene))[i]->faceList[j]->vertex_index[1] ]->e[1],
                    (*GetListFig(scene))[i]->vertexList[ (*GetListFig(scene))[i]->faceList[j]->vertex_index[1] ]->e[2]);

            tr.c = Point3D((*GetListFig(scene))[i]->vertexList[ (*GetListFig(scene))[i]->faceList[j]->vertex_index[2] ]->e[0],
                    (*GetListFig(scene))[i]->vertexList[ (*GetListFig(scene))[i]->faceList[j]->vertex_index[2] ]->e[1],
                    (*GetListFig(scene))[i]->vertexList[ (*GetListFig(scene))[i]->faceList[j]->vertex_index[2] ]->e[2]);

            tr.a = tr.a + Point3D(currentFrame->width() / 2, currentFrame->height() / 2, 0);
            tr.b = tr.b + Point3D(currentFrame->width() / 2, currentFrame->height() / 2, 0);
            tr.c = tr.c + Point3D(currentFrame->width() / 2, currentFrame->height() / 2, 0);
            PutTriangle(tr, QColor(listColors[(i + 3) * 3]).rgb());
        }
    }
    emit PaintingDoneSignal(currentFrame);
}

static int nAll = 0, nRewrite = 0;

void SimpleZBuffer::PutTriangle(triangle &t, uint color)
{
    int ysc, e1, e;
    double ymax,ymin;
    double x[3], y[3];
    double z_a[3];
    //Заносим x,y из t в массивы для последующей работы с ними
    x[0] = int(t.a.x), y[0] = int(t.a.y);
    x[1] = int(t.b.x), y[1] = int(t.b.y);
    x[2] = int(t.c.x), y[2] = int(t.c.y);
    z_a[0] = t.a.z, z_a[1] = t.b.z, z_a[2] = t.c.z;
    //Определяем максимальный и минимальный y
    ymax = ymin = y[0];

    if (ymax < y[1])
        ymax = y[1];
    else
        if (ymin > y[1])
            ymin = y[1];

    if (ymax < y[2])
        ymax = y[2];
    else
        if (ymin > y[2])
            ymin = y[2];

    ymin = (ymin < 0) ? 0 : ymin;
    ymax = (ymax < sY) ? ymax : sY;

    int ne;
    double x1, x2;
    int xsc1, xsc2;
    double z1, z2, tc, z;
    //Следующий участок кода перебирает все строки сцены
    //и определяет глубину каждого пикселя
    //для соответствующего треугольника
    for (ysc = (int)ymin; ysc < (int)ymax; ysc++)
    {
        ne = 0;
        for (int e = 0; e < 3; e++)
        {
            e1 = e + 1;
            if (e1 == 3)
                e1 = 0;

            if (y[e] < y[e1])
            {
                if (y[e1] <= ysc || ysc < y[e])
                    continue;
            }
            else
                if (y[e] > y[e1])
                {
                    if (y[e1] > ysc || ysc >= y[e])
                        continue;
                }
                else
                    continue;

            tc = double(y[e] - ysc) / (y[e] - y[e1]);
            if (ne)
            {
                x2 = x[e] +  ( tc * (x[e1] - x[e]) );
                z2 = z_a[e] + tc * (z_a[e1] - z_a[e]);
            }
            else
            {
                x1 = x[e] +  ( tc * (x[e1] - x[e]) );
                z1 = z_a[e] + tc * (z_a[e1] - z_a[e]);
                ne = 1;
            }
        }

        double temp;
        if (x2 < x1)
        {
            temp = x1;
            x1 = x2;
            x2 = temp;
            tc = z1;
            z1 = z2;
            z2 = tc;
        }

        xsc1 = (x1 < 0) ? 0 : x1;
        xsc2 = (x2 < sX) ? x2 : sX;
        for (int xsc = xsc1; xsc < xsc2; xsc++)
        {
            tc = double(x1 - xsc) / (x1 - x2);
            z = z1 + tc * (z2 - z1);
            //Если полученная глубина пиксела меньше той,
            //что находится в Z-Буфере - заменяем храняшуюся на новую.
            if (z > buff[xsc][ysc])
            {
                /*
                (*( buff[ ysc ] + xsc )).R = t.R;
                (*( buff[ ysc ] + xsc )).G = t.G;
                (*( buff[ ysc ] + xsc )).B = t.B;

                (*( buff[ ysc ] + xsc )).z = z; */

                buff[xsc][ysc] = z;
                currentFrame->setPixel(xsc, sY - ysc - 1, color);
            }
        }
    }
}
