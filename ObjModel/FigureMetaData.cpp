#include "FigureMetaData.h"
#include "ObjModel.h"

FigureMetaData::FigureMetaData()
{
    angle = 0;
}

FigureMetaData::FigureMetaData(QString name, QString category)
{
    angle = 0;
    this->name = name;
    this->category = category;
    pos = QPointF(0, 0);

    LoadAndCalcMinMax();
}

QString FigureMetaData::GetName() const
{
    return name;
}

void FigureMetaData::SetName(QString name)
{
    this->name = name;
}

QString FigureMetaData::GetCategory() const
{
    return category;
}

void FigureMetaData::SetCategory(QString category)
{
    this->category = category;
}

QPointF FigureMetaData::GetPntMin() const
{
    return pntMin;
}

QPointF FigureMetaData::GetPntMax() const
{
    return pntMax;
}

int FigureMetaData::AddAngle(int addingAngle)
{
    angle += addingAngle;

    if (angle < 0)
        angle = 360 + angle % 360;

    if (angle >= 360)
        angle %= 360;

    return angle;
}

void FigureMetaData::SetPos(QPointF pos)
{
    this->pos = pos;
}

void FigureMetaData::SetPos(qreal posX, qreal posY)
{
    pos.setX(posX);
    pos.setY(posY);
}

QPointF FigureMetaData::GetPos() const
{
    return pos;
}

void FigureMetaData::LoadAndCalcMinMax()
{
    if (name.isEmpty())
        throw "Name is empty";

    ObjLoader objLoader;
    objLoader.load(QString("models/" + category + "/" + name).toLocal8Bit().constData());
    ObjModel objModel(objLoader);

    Point3D pnt3DMin = objModel.MinPoint();
    Point3D pnt3DMax = objModel.MaxPoint();

    pntMin.setX(pnt3DMin.x);
    pntMin.setY(pnt3DMin.y);

    pntMax.setX(pnt3DMax.x);
    pntMax.setY(pnt3DMax.y);
}
