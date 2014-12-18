#include "ColorSimpleZBuffer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

ColorSimpleZBuffer::ColorSimpleZBuffer(int ax, int ay, QObject *parent) : SimpleZBuffer(ax, ay, parent)
{
}

ColorSimpleZBuffer::~ColorSimpleZBuffer()
{

}

void ColorSimpleZBuffer::Paint(Scene &scene)
{
    Clear();
    QStringList listColors = QColor::colorNames();
    for (int i = 0; i < GetListFig(scene)->size(); ++i)
    {
        bool hasNormals = ((*GetListFig(scene))[i]->normalCount > 0) ? (true) : (false);
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

            tr.a = tr.a + Point3D(currentFrame->width() / 2, currentFrame->height() / 2.25, 0);
            tr.b = tr.b + Point3D(currentFrame->width() / 2, currentFrame->height() / 2.25, 0);
            tr.c = tr.c + Point3D(currentFrame->width() / 2, currentFrame->height() / 2.25, 0);


            if (isFarthest(tr))
                continue;
            /*
            if (j % 2 == 0 && i > GetListFig(scene)->size() - 3)
                if (!(hasNormals && isFront(tr, (*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[0] ])))
                {
                    wasUnfront = true;
                    continue;
                }
            */
            if (hasNormals && !isFront(tr, (*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[0] ]))
                continue;

            QColor color;
            if ((*GetListFig(scene))[i]->materialCount > 0)
                color.setRgb(
                    (*GetListFig(scene))[i]->materialList[ (*GetListFig(scene))[i]->faceList[j]->material_index ]->diff[0] * 255.0,
                    (*GetListFig(scene))[i]->materialList[ (*GetListFig(scene))[i]->faceList[j]->material_index ]->diff[1] * 255.0,
                    (*GetListFig(scene))[i]->materialList[ (*GetListFig(scene))[i]->faceList[j]->material_index ]->diff[2]* 255.0);
            else
               color = QColor(listColors[(i + 3) * 3]);

            PutTriangle(tr, color.rgb());
        }
    }
    emit PaintingDoneSignal(currentFrame);
}

bool ColorSimpleZBuffer::isFarthest(triangle &tr)
{
    if (tr.a.x <= 0 || tr.a.x >= sX || tr.a.y <= 0 || tr.a.y >= sY ||
            tr.b.x <= 0 || tr.b.x >= sX || tr.b.y <= 0 || tr.b.y >= sY ||
            tr.c.x <= 0 || tr.c.x >= sX || tr.c.y <= 0 || tr.c.y >= sY)
        return false;

    const int maxLen = 30; // Максимальная длина проекции, для которой этот метод фильтрации выполняется
    if (fabs(tr.a.x - tr.b.x) > maxLen || fabs(tr.a.x - tr.c.x) > maxLen || fabs(tr.c.x - tr.b.x) > maxLen ||
        fabs(tr.a.y - tr.b.y) > maxLen || fabs(tr.a.y - tr.c.y) > maxLen || fabs(tr.c.y - tr.b.y) > maxLen)
                return false;

    if ((tr.a.z < buff[int(tr.a.x)][int(tr.a.y)]) && (tr.b.z < buff[int(tr.b.x)][int(tr.b.y)])
            && (tr.c.z < buff[int(tr.c.x)][int(tr.c.y)]))
        return true;
    else
        return false;
}

bool ColorSimpleZBuffer::isFront(triangle &tr, ObjVector *normal)
{
    Point3D a(tr.b.x - tr.a.x, tr.b.y - tr.a.y, tr.b.z - tr.a.z);
    Point3D b(tr.c.x - tr.a.x, tr.c.y - tr.a.y, tr.c.z - tr.a.z);

    ObjVector mult;
    mult.e[0] = a.y * b.z - a.z * b.y;
    mult.e[1] = a.z * b.x - a.x * b.z;
    mult.e[2] = a.x * b.y - a.y * b.x;

    qreal multScalar = mult.e[0] * normal->e[0] + mult.e[1] * normal->e[1] + mult.e[2] * normal->e[2];
    if (multScalar < 0)
    {
        /*
        mult.e[0] = - mult.e[0];
        mult.e[1] = - mult.e[1];
        */
        mult.e[2] = - mult.e[2]; // нужно только это
    }

    if (mult.e[2] > 0)
        return true;
    else
        return false;
}
