#ifndef GRAPHICSFURNITUREITEM_H
#define GRAPHICSFURNITUREITEM_H

#include <QGraphicsItem>
#include "ObjModel/FigureMetaData.h"
#include <QVector>

class GraphicsFurnitureItem : public QGraphicsItem
{
public:
    //explicit GraphicsFurnitureItem(QGraphicsItem *parent = 0);
    GraphicsFurnitureItem(FigureMetaData *it, QGraphicsItem *parent = 0);
    ~GraphicsFurnitureItem() {}

private:
    FigureMetaData *itFigureMetaData;

private:
    qreal GetWidth() const;
    qreal GetHeight() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

};

#endif // GRAPHICSFURNITUREITEM_H
