#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <QObject>
#include "ObjLoader/ObjLoader.h"
#include "Points.h"
#include <QVector>

class ObjModel : public QObject
{
    Q_OBJECT
public:
    explicit ObjModel(ObjLoader &objLoader);

private:
    QVector<Point3D> vecPnts3D;
    QVector<FaceIndexes> vecIndx;

private:
    void fillDataFromObjLoader(ObjLoader &objLoader);

};

#endif // OBJMODEL_H
