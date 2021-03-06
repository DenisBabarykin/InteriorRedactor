#include "FigureMetaData.h"
#include "./Figure/SimpleFigure.h"
#include <QDebug>

int FigureMetaData::GetAngle() const
{
    return angle;
}

void FigureMetaData::SetAngle(int value)
{
    angle = value;
}

QString FigureMetaData::GetFileName()
{
    return QString("models/" + category + "/" + name);
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

    Figure objLoader;
    //const char *ch = ("models/" + category + "/" + name).toLocal8Bit().constData();
    objLoader.load(QString("models/" + category + "/" + name).toLocal8Bit().constData());
    SimpleFigure objModel(objLoader);

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
    bool doub = (sizeof(qreal) == sizeof(double)) ? (true) : (false);

    fig.name = in.readLine();
    fig.category = in.readLine();

    qreal x = 0, y = 0;
    x = (doub) ? (in.readLine().toDouble()) : (in.readLine().toFloat());
    y = (doub) ? (in.readLine().toDouble()) : (in.readLine().toFloat());
    fig.pntMin = QPointF(x, y);

    x = (doub) ? (in.readLine().toDouble()) : (in.readLine().toFloat());
    y = (doub) ? (in.readLine().toDouble()) : (in.readLine().toFloat());
    fig.pntMax = QPointF(x, y);

    fig.angle = QString(in.readLine().data()).toInt();

    x = (doub) ? (in.readLine().toDouble()) : (in.readLine().toFloat());
    y = (doub) ? (in.readLine().toDouble()) : (in.readLine().toFloat());
    fig.pos = QPointF(x, y);

    fig.hasPreview = (in.readLine() == QString("has_preview")) ? (true) : (false);

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
    out << ((fig.HasPreview()) ? ("has_preview") : ("no_preview")) << endl;

    return out;
}
