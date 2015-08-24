#include "SimpleLightZBuffer.h"
#include "math.h"
#include <QDebug>

SimpleLightZBuffer::SimpleLightZBuffer(int ax, int ay, QObject *parent) : SimpleZBuffer(ax, ay, parent)
{
}

SimpleLightZBuffer::~SimpleLightZBuffer()
{
}

void SimpleLightZBuffer::Paint(Scene &scene)
{
    Clear();
    QStringList listColors = QColor::colorNames();
    for (int i = 0; i < GetListFig(scene)->size(); ++i)
    {
        if (i == GetListFig(scene)->size() - 2)  // Чтобы не рисовать стены
            continue;
        for (int j = 0; j < (*GetListFig(scene))[i]->faceCount; ++j)
        {
            Polygon tr;

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


            tr.na = Point3D((*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[0] ]->e[0],
                    (*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[0] ]->e[1],
                    (*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[0] ]->e[2]);

            tr.nb = Point3D((*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[1] ]->e[0],
                    (*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[1] ]->e[1],
                    (*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[1] ]->e[2]);

            tr.nc = Point3D((*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[2] ]->e[0],
                    (*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[2] ]->e[1],
                    (*GetListFig(scene))[i]->normalList[ (*GetListFig(scene))[i]->faceList[j]->normal_index[2] ]->e[2]);

            QColor color;
            if ((*GetListFig(scene))[i]->materialCount > 0)
                color.setRgbF(
                    (*GetListFig(scene))[i]->materialList[ (*GetListFig(scene))[i]->faceList[j]->material_index ]->diff[0],
                    (*GetListFig(scene))[i]->materialList[ (*GetListFig(scene))[i]->faceList[j]->material_index ]->diff[1],
                    (*GetListFig(scene))[i]->materialList[ (*GetListFig(scene))[i]->faceList[j]->material_index ]->diff[2]);
            else
               color = QColor(listColors[(i + 3) * 3]);

            PutTriangle(tr, color);
        }
    }
    emit PaintingDoneSignal(currentFrame);
}

void SimpleLightZBuffer::PutTriangle(Polygon &t, QColor color)
{
    int ysc, e1;
    double ymax, ymin;
    double x[3], y[3];
    double z_a[3];
    QColor intense[3];
    //Заносим x,y из t в массивы для последующей работы с ними
    x[0] = int(t.a.x), y[0] = int(t.a.y);
    x[1] = int(t.b.x), y[1] = int(t.b.y);
    x[2] = int(t.c.x), y[2] = int(t.c.y);
    z_a[0] = t.a.z, z_a[1] = t.b.z, z_a[2] = t.c.z;

    double Cos[3];
    Cos[0] = GetCos(t.na);
    Cos[1] = GetCos(t.nb);
    Cos[2] = GetCos(t.nc);
    intense[0].setRgbF(color.redF() * Cos[0], color.greenF() * Cos[0], color.blueF() * Cos[0]);
    intense[1].setRgbF(color.redF() * Cos[1], color.greenF() * Cos[1], color.blueF() * Cos[1]);
    intense[2].setRgbF(color.redF() * Cos[2], color.greenF() * Cos[2], color.blueF() * Cos[2]);
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
    double i1[3], i2[3], cur_i[3];
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
                i2[0] = intense[e].redF() + tc * (intense[e1].redF() - intense[e].redF());
                i2[1] = intense[e].greenF() + tc * (intense[e1].greenF() - intense[e].greenF());
                i2[2] = intense[e].blueF() + tc * (intense[e1].blueF() - intense[e].blueF());
            }
            else
            {
                x1 = x[e] +  ( tc * (x[e1] - x[e]) );
                z1 = z_a[e] + tc * (z_a[e1] - z_a[e]);
                i1[0] = intense[e].redF() + tc * (intense[e1].redF() - intense[e].redF());
                i1[1] = intense[e].greenF() + tc * (intense[e1].greenF() - intense[e].greenF());
                i1[2] = intense[e].blueF() + tc * (intense[e1].blueF() - intense[e].blueF());
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
            for (int i = 0; i < 3; ++i)
            {
                temp = i1[i];
                i1[i] = i2[i];
                i2[i] = temp;
            }
        }

        xsc1 = (x1 < 0) ? 0 : x1;
        xsc2 = (x2 < sX) ? x2 : sX;
        for (int xsc = xsc1; xsc < xsc2; xsc++)
        {
            tc = double(x1 - xsc) / (x1 - x2);
            z = z1 + tc * (z2 - z1);

            for (int i = 0; i < 3; ++i)
            {
                cur_i[i] = i1[i] + tc * (i2[i] - i1[i]);
                cur_i[i] = (cur_i[i] > 0) ? (cur_i[i]) : (0);
                cur_i[i] = (cur_i[i] < 1) ? (cur_i[i]) : (1);
            }

            //Если полученная глубина пиксела меньше той,
            //что находится в Z-Буфере - заменяем храняшуюся на новую.
            if (z > buff[xsc][ysc])
            {
                buff[xsc][ysc] = z;
                QColor resColor;
                resColor.setRgbF(cur_i[0], cur_i[1], cur_i[2]);
                currentFrame->setPixel(xsc, sY - ysc - 1, resColor.rgb());
            }
        }
    }
}

double SimpleLightZBuffer::GetCos(Point3D normal)
{
    double zn = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (!zn)
        return 1;
    double res = fabs(normal.z / zn);
    if (res > 1 || res < 0)
        qDebug() << res;
    return res;
}
