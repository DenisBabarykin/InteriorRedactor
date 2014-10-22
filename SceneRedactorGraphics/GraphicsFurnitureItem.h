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

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    FigureMetaData *itFigureMetaData;

private:
    qreal GetWidth() const;
    qreal GetHeight() const;

};

#endif // GRAPHICSFURNITUREITEM_H
