#include "ObjModel.h"
#include <QtMath>
#include <QDebug>

const double Pi = 3.14159265;

ObjModel::ObjModel()
{

}

ObjModel::ObjModel(ObjLoader &objLoader)
{
    FillDataFromObjLoader(objLoader);
    Center();
}

void ObjModel::FillDataFromObjLoader(ObjLoader &objLoader)
{
    vecPnts3D.resize(objLoader.vertexCount);
    vecIndx.resize(objLoader.faceCount);

    for (int i = 0; i < vecPnts3D.count(); ++i)
        vecPnts3D[i] = Point3D(objLoader.vertexList[i]->e[0], objLoader.vertexList[i]->e[1],
                objLoader.vertexList[i]->e[2]);

    int nQuads = 0;
    for (int i = 0; i < vecIndx.count(); ++i)
    {
        if (objLoader.faceList[i]->vertex_count != 3)
            //throw ("Vertex count error");
            ++nQuads;

        vecIndx[i] = FaceIndexes(objLoader.faceList[i]->vertex_index[0],
                objLoader.faceList[i]->vertex_index[1], objLoader.faceList[i]->vertex_index[2]);
    }
    qDebug() << nQuads;
}

Point3D ObjModel::MaxPoint()
{
    Point3D maxPoint = vecPnts3D[0];

    for (int i = 0; i < vecPnts3D.count(); ++i)
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

Point3D ObjModel::MinPoint()
{
    Point3D MinPoint = vecPnts3D[0];

    for (int i = 0; i < vecPnts3D.count(); ++i)
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

void ObjModel::Shift(const ObjModel *baseModel, qreal dx, qreal dy, qreal dz)
{
    for (int i = 0; i < vecPnts3D.count(); ++i)
    {
        vecPnts3D[i].x = baseModel->vecPnts3D[i].x + dx;
        vecPnts3D[i].y = baseModel->vecPnts3D[i].y + dy;
        vecPnts3D[i].z = baseModel->vecPnts3D[i].z + dz;
    }
}

void ObjModel::Center()
{
    Point3D maxPoint = MaxPoint();
    Point3D minPoint = MinPoint();

    double dx = - (maxPoint.x + minPoint.x) / 2;
    double dy = - minPoint.y;
    double dz = - (maxPoint.z + minPoint.z) / 2;

    for (int i = 0; i < vecPnts3D.count(); ++i)
    {
        vecPnts3D[i].x += dx;
        vecPnts3D[i].y += dy;
        vecPnts3D[i].z += dz;
    }

    //Shift(0, -minPoint.y, 0);
}

void ObjModel::DrawModel(QPainter &painter)
{
    for (int i = 0; i < vecIndx.count(); ++i)
    {
        painter.drawLine(vecPnts3D[vecIndx[i].v1].x, vecPnts3D[vecIndx[i].v1].y, vecPnts3D[vecIndx[i].v2].x,
                vecPnts3D[vecIndx[i].v2].y);

        painter.drawLine(vecPnts3D[vecIndx[i].v1].x, vecPnts3D[vecIndx[i].v1].y, vecPnts3D[vecIndx[i].v3].x,
                vecPnts3D[vecIndx[i].v3].y);

        painter.drawLine(vecPnts3D[vecIndx[i].v2].x, vecPnts3D[vecIndx[i].v2].y, vecPnts3D[vecIndx[i].v3].x,
                vecPnts3D[vecIndx[i].v3].y);
    }
}

void ObjModel::RotateOX(double angle)
{
    angle *= Pi / 180;
    for (int i = 0; i < vecPnts3D.count(); ++i)
    {
        int y = vecPnts3D[i].y * cos(angle) - vecPnts3D[i].z * sin(angle);
        int z = vecPnts3D[i].y * sin(angle) + vecPnts3D[i].z * cos(angle);
        vecPnts3D[i].y = y;
        vecPnts3D[i].z = z;
    }
}

void ObjModel::DrawModelFill(QPainter &painter)
{
    QPointF *points = new QPointF[4];

    painter.setBrush(QBrush(Qt::black));
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < vecIndx.count(); ++i)
    {
        points[0] = QPointF(vecPnts3D[vecIndx[i].v1].x, vecPnts3D[vecIndx[i].v1].y);
        points[1] = QPointF(vecPnts3D[vecIndx[i].v2].x, vecPnts3D[vecIndx[i].v2].y);
        points[2] = QPointF(vecPnts3D[vecIndx[i].v3].x, vecPnts3D[vecIndx[i].v3].y);

        painter.drawPolygon(points, 3);

    }
    painter.setBrush(QBrush(Qt::white));

    delete [] points;
}

void ObjModel::RotateOY(double angle)
{
    angle *= Pi / 180;
    for (int i = 0; i < vecPnts3D.count(); ++i)
    {
        int x = vecPnts3D[i].x * cos(angle) + vecPnts3D[i].z * sin(angle);
        int z = - vecPnts3D[i].x * sin(angle) + vecPnts3D[i].z * cos(angle);
        vecPnts3D[i].x = x;
        vecPnts3D[i].z = z;
    }
}

void ObjModel::Rotate(const ObjModel *baseModel, int angleOX, int angleOY)
{
    if (!angleOX)
    {
        angleOY *= Pi / 180;
        for (int i = 0; i < vecPnts3D.count(); ++i)
        {
            vecPnts3D[i].x = baseModel->vecPnts3D[i].x * cos(angleOY) + baseModel->vecPnts3D[i].z * sin(angleOY);
            vecPnts3D[i].z = - baseModel->vecPnts3D[i].x * sin(angleOY) + baseModel->vecPnts3D[i].z * cos(angleOY);
            vecPnts3D[i].y = baseModel->vecPnts3D[i].y;
        }
    }
    else if (!angleOY)
    {
        angleOX *= Pi / 180;
        for (int i = 0; i < vecPnts3D.count(); ++i)
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
        for (int i = 0; i < vecPnts3D.count(); ++i)
        {
            vecPnts3D[i].y = baseModel->vecPnts3D[i].y * cos(angleOX) -  baseModel->vecPnts3D[i].z * sin(angleOX);
            int newZ = vecPnts3D[i].y * sin(angleOX) + vecPnts3D[i].z * cos(angleOX);

            vecPnts3D[i].x = baseModel->vecPnts3D[i].x * cos(angleOY) + newZ * sin(angleOY);
            vecPnts3D[i].z = - baseModel->vecPnts3D[i].x * sin(angleOY) + newZ * cos(angleOY);
        }
    }
}

void ObjModel::Perspective()
{
    qreal fov = 500;
    qreal absZ;
    for (int i = 0; i < vecPnts3D.count(); ++i)
    {
        absZ = fabs(vecPnts3D[i].z);
        //absZ = vecPnts3D[i].z;
        vecPnts3D[i].x =  vecPnts3D[i].x / absZ * fov;
        vecPnts3D[i].y =  vecPnts3D[i].y / absZ * fov;
    }
}
