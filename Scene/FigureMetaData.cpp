#include "FigureMetaData.h"
#include "ObjModel.h"
#include <QDebug>

int FigureMetaData::GetAngle() const
{
    return angle;
}

void FigureMetaData::SetAngle(int value)
{
    angle = value;
}

FigureMetaData::FigureMetaData()
{
    angle = 0;
    pos = QPointF(0.0, 0.0);
    hasPreview = false;
}

FigureMetaData::FigureMetaData(QString name, QString category)
{
    angle = 0;
    this->name = name;
    this->category = category;
    pos = QPointF(0.0, 0.0);
    hasPreview = false;

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

bool FigureMetaData::HasPreview() const
{
    return hasPreview;
}

void FigureMetaData::SetPreviewStatus(bool hasPreview)
{
    this->hasPreview = hasPreview;
}

void FigureMetaData::LoadAndCalcMinMax()
{
    if (name.isEmpty())
        throw "Name is empty";

    ObjLoader objLoader;
    const char *ch = ("models/" + category + "/" + name).toLocal8Bit().constData();
    objLoader.load(QString("models/" + category + "/" + name).toLocal8Bit().constData());
    ObjModel objModel(objLoader);

    Point3D pnt3DMin = objModel.MinPoint();
    Point3D pnt3DMax = objModel.MaxPoint();

    pntMin.setX(pnt3DMin.x);
    pntMin.setY(pnt3DMin.z);

    pntMax.setX(pnt3DMax.x);
    pntMax.setY(pnt3DMax.z);

    qDebug() << name << " " << pntMax.rx() - pntMin.rx() << " " << pntMax.ry() - pntMin.ry();
}

QTextStream &operator>>(QTextStream &in, FigureMetaData &fig)
{
    in >> fig.name;
    in >> fig.category;

    qreal x = 0, y = 0;
    in >> x;
    in >> y;
    fig.pntMin.setX(x);
    fig.pntMin.setY(y);

    in >> x;
    in >> y;
    fig.pntMax.setX(x);
    fig.pntMax.setY(y);

    in >> fig.angle;

    in >> x;
    in >> y;
    fig.SetPos(x, y);

    int previewStat;
    in >> previewStat;
    if (previewStat == 1)
        fig.hasPreview = true;
    else
        fig.hasPreview = false;

    return in;
}

QTextStream &operator<<(QTextStream &out, const FigureMetaData &fig)
{
    out << fig.GetName() << endl;
    out << fig.GetCategory() << endl;
    out << fig.GetPntMin().rx() << endl;
    out << fig.GetPntMin().ry() << endl;
    out << fig.GetPntMax().rx() << endl;
    out << fig.GetPntMax().ry() << endl;
    out << fig.GetAngle() << endl;
    out << fig.GetPos().rx() << endl;
    out << fig.GetPos().ry() << endl;
    out << ((fig.HasPreview()) ? (1) : (0)) << endl;

    return out;
}
