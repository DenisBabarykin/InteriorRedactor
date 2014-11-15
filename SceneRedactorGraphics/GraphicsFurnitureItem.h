#ifndef GRAPHICSFURNITUREITEM_H
#define GRAPHICSFURNITUREITEM_H

#include <QGraphicsItem>
#include "Scene/FigureMetaData.h"
#include <QVector>

class GraphicsFurnitureItem : public QGraphicsItem
{
public:
    //explicit GraphicsFurnitureItem(QGraphicsItem *parent = 0);
    GraphicsFurnitureItem(FigureMetaData *fig, QGraphicsItem *parent = 0);
    ~GraphicsFurnitureItem() {}

    bool isContain(const FigureMetaData *fig) const;

private:
    FigureMetaData *figureMetaData;

private:
    qreal GetWidth() const;
    qreal GetHeight() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

};

#endif // GRAPHICSFURNITUREITEM_H
