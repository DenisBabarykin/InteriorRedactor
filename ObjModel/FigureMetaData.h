#ifndef FIGUREMETADATA_H
#define FIGUREMETADATA_H

#include <QString>
#include <QPointF>

class FigureMetaData
{
private:
    QString name;
    QString category;

    QPointF pntMin;
    QPointF pntMax;

    int angle;

public:
    FigureMetaData();
    FigureMetaData(QString name, QString category);

    QString GetName() const;
    void SetName(QString name);

    QString GetCategory() const;
    void SetCategory(QString category);

    QPointF GetPntMin() const;
    QPointF GetPntMax() const;

    int AddAngle(int addingAngle);

    void LoadAndCalcMinMax();
};

#endif // FIGUREMETADATA_H
