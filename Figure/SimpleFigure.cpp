#include "SimpleFigure.h"
#include <QtMath>
#include <QDebug>

const double Pi = 3.14159265;

SimpleFigure::SimpleFigure()
{

}

SimpleFigure::~SimpleFigure()
{
    vecPnts3D.clear();
    vecIndx.clear();
}

SimpleFigure::SimpleFigure(Figure &objLoader)
{
    FillDataFromObjLoader(objLoader);
    Center();
}

void SimpleFigure::FillDataFromObjLoader(Figure &objLoader)
{
    vecPnts3D.resize(objLoader.vertexCount);
    vecIndx.resize(objLoader.faceCount);

    for (uint i = 0; i < vecPnts3D.size(); ++i)
        vecPnts3D[i] = Point3D(objLoader.vertexList[i]->e[0], objLoader.vertexList[i]->e[1],
                objLoader.vertexList[i]->e[2]);

    int nQuads = 0;
    for (uint i = 0; i < vecIndx.size(); ++i)
    {
        if (objLoader.faceList[i]->vertex_count != 3)
            //throw ("Vertex count error");
            ++nQuads;

        vecIndx[i] = FaceIndexes(objLoader.faceList[i]->vertex_index[0],
                objLoader.faceList[i]->vertex_index[1], objLoader.faceList[i]->vertex_index[2]);
    }
    qDebug() << nQuads;
}

Point3D SimpleFigure::MaxPoint()
{
    Point3D maxPoint = vecPnts3D[0];

    for (uint i = 0; i < vecPnts3D.size(); ++i)
    {
        if (vecPnts3D[i].x > maxPoint.x)
            maxPoint.x = vecPnts3D[i].x;

        if (vecPnts3D[i].y > maxPoint.y)
            maxPoint.y = vecPnts3D[i].y;

        if (vecPnts3D[i].z > maxPoint.z)
            maxPoint.z = vecPnts3D[i].z;
    }

    return maxPoint;
}

Point3D SimpleFigure::MinPoint()
{
    Point3D MinPoint = vecPnts3D[0];

    for (uint i = 0; i < vecPnts3D.size(); ++i)
    {
        if (vecPnts3D[i].x < MinPoint.x)
            MinPoint.x = vecPnts3D[i].x;

        if (vecPnts3D[i].y < MinPoint.y)
            MinPoint.y = vecPnts3D[i].y;

        if (vecPnts3D[i].z < MinPoint.z)
            MinPoint.z = vecPnts3D[i].z;
    }

    return MinPoint;
}

void SimpleFigure::Shift(const SimpleFigure *baseModel, qreal dx, qreal dy, qreal dz)
{
    for (uint i = 0; i < vecPnts3D.size(); ++i)
    {
        vecPnts3D[i].x = baseModel->vecPnts3D[i].x + dx;
        vecPnts3D[i].y = baseModel->vecPnts3D[i].y + dy;
        vecPnts3D[i].z = baseModel->vecPnts3D[i].z + dz;
    }
}

void SimpleFigure::Center()
{
    Point3D maxPoint = MaxPoint();
    Point3D minPoint = MinPoint();

    double dx = - (maxPoint.x + minPoint.x) / 2;
    double dy = - minPoint.y;
    double dz = - (maxPoint.z + minPoint.z) / 2;

    for (uint i = 0; i < vecPnts3D.size(); ++i)
    {
        vecPnts3D[i].x += dx;
        vecPnts3D[i].y += dy;
        vecPnts3D[i].z += dz;
    }

    //Shift(0, -minPoint.y, 0);
}

void SimpleFigure::DrawModel(QPainter &painter)
{
    for (uint i = 0; i < vecIndx.size(); ++i)
    {
        painter.drawLine(vecPnts3D[vecIndx[i].v1].x, vecPnts3D[vecIndx[i].v1].y, vecPnts3D[vecIndx[i].v2].x,
                vecPnts3D[vecIndx[i].v2].y);

        painter.drawLine(vecPnts3D[vecIndx[i].v1].x, vecPnts3D[vecIndx[i].v1].y, vecPnts3D[vecIndx[i].v3].x,
                vecPnts3D[vecIndx[i].v3].y);

        painter.drawLine(vecPnts3D[vecIndx[i].v2].x, vecPnts3D[vecIndx[i].v2].y, vecPnts3D[vecIndx[i].v3].x,
                vecPnts3D[vecIndx[i].v3].y);
    }
}

void SimpleFigure::Rotate(const SimpleFigure *baseModel, qreal angleOX, qreal angleOY)
{
    if (!angleOX)
    {
        angleOY *= Pi / 180;
        for (uint i = 0; i < vecPnts3D.size(); ++i)
        {
            vecPnts3D[i].x = baseModel->vecPnts3D[i].x * cos(angleOY) + baseModel->vecPnts3D[i].z * sin(angleOY);
            vecPnts3D[i].z = - baseModel->vecPnts3D[i].x * sin(angleOY) + baseModel->vecPnts3D[i].z * cos(angleOY);
            vecPnts3D[i].y = baseModel->vecPnts3D[i].y;
        }
    }
    else if (!angleOY)
    {
        angleOX *= Pi / 180;
        for (uint i = 0; i < vecPnts3D.size(); ++i)
        {
            vecPnts3D[i].x = baseModel->vecPnts3D[i].x;
            vecPnts3D[i].y = baseModel->vecPnts3D[i].y * cos(angleOX) - baseModel->vecPnts3D[i].z * sin(angleOX);
            vecPnts3D[i].z = baseModel->vecPnts3D[i].y * sin(angleOX) + baseModel->vecPnts3D[i].z * cos(angleOX);
        }
    }
    else
    {
        angleOX *= Pi / 180;
        angleOY *= Pi / 180;
        for (uint i = 0; i < vecPnts3D.size(); ++i)
        {
            vecPnts3D[i].x = baseModel->vecPnts3D[i].x * cos(angleOY) + baseModel->vecPnts3D[i].z * sin(angleOY);
            qreal newZ = - baseModel->vecPnts3D[i].x * sin(angleOY) + baseModel->vecPnts3D[i].z * cos(angleOY);

            vecPnts3D[i].y = baseModel->vecPnts3D[i].y * cos(angleOX) - newZ * sin(angleOX);
            vecPnts3D[i].z = baseModel->vecPnts3D[i].y * sin(angleOX) + newZ * cos(angleOX);
        }
    }
}

void SimpleFigure::Perspective(const SimpleFigure *baseModel)
{
    qreal fov = 500;
    qreal absZ;
    for (uint i = 0; i < vecPnts3D.size(); ++i)
    {
        absZ = fabs(vecPnts3D[i].z);
        //absZ = vecPnts3D[i].z;
        vecPnts3D[i].x =  baseModel->vecPnts3D[i].x / absZ * fov;
        vecPnts3D[i].y =  baseModel->vecPnts3D[i].y / absZ * fov;
    }
   // qDebug() << this;
}
