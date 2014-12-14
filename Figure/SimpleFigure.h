#ifndef SIMPLEFIGURE_H
#define SIMPLEFIGURE_H

#include "Figure.h"
#include "MeasuredFigure.h"
#include "./Points/Points.h"
#include <QVector>
#include <QPainter>

class SimpleFigure : public virtual MeasuredFigure
{
public:
    SimpleFigure();
    ~SimpleFigure();
    explicit SimpleFigure(Figure &objLoader);

    void DrawModel(QPainter &painter);
    void Rotate(const SimpleFigure *baseModel, qreal angleOX, qreal angleOY);
    void Perspective(const SimpleFigure *baseModel);

    virtual Point3D MaxPoint();
    virtual Point3D MinPoint();

    void Shift(const SimpleFigure *baseModel, qreal dx, qreal dy, qreal dz); // Сдвиг относительно базовой модели

public: //private:
    std::vector<Point3D> vecPnts3D;
    std::vector<FaceIndexes> vecIndx;

private:
    void FillDataFromObjLoader(Figure &objLoader);
    void Center();

};

#endif // SIMPLEFIGURE_H
