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
            //PutTriangle(tr, QColor(listColors[(i + 3) * 3]).rgb());
            if ((*GetListFig(scene))[i]->materialCount > 0)
                PutTriangle(tr, QColor((*GetListFig(scene))[i]->materialList[ (*GetListFig(scene))[i]->faceList[j]->material_index ]->diff[0] * 255.0,
                    (*GetListFig(scene))[i]->materialList[ (*GetListFig(scene))[i]->faceList[j]->material_index ]->diff[1] * 255.0,
                    (*GetListFig(scene))[i]->materialList[ (*GetListFig(scene))[i]->faceList[j]->material_index ]->diff[2]
                    * 255.0).rgb());
            else
                PutTriangle(tr, QColor(listColors[(i + 3) * 3]).rgb());
        }
    }
    emit PaintingDoneSignal(currentFrame);
}
