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

    QPointF pos;

    bool hasPreview; // Наличие файла картинки предпросмотра

public:
    FigureMetaData();
    FigureMetaData(QString name, QString category);
    FigureMetaData(const FigureMetaData &obj)
    {
        name = obj.name;
        category = obj.category;
        pntMin = obj.pntMin;
        pntMax = obj.pntMax;
        angle = obj.angle;
        pos = obj.pos;
        hasPreview = obj.hasPreview;
    }

    ~FigureMetaData() {}

    QString GetName() const;
    void SetName(QString name);

    QString GetCategory() const;
    void SetCategory(QString category);

    QPointF GetPntMin() const;
    QPointF GetPntMax() const;

    int AddAngle(int addingAngle);

    void SetPos(QPointF pos);
    void SetPos(qreal posX, qreal posY);

    QPointF GetPos() const;

    bool HasPreview() const;
    void SetPreviewStatus(bool hasPreview);

    void LoadAndCalcMinMax();
};

#endif // FIGUREMETADATA_H
