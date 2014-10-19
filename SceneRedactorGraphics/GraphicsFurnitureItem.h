#ifndef GRAPHICSFURNITUREITEM_H
#define GRAPHICSFURNITUREITEM_H

#include <QGraphicsItem>
#include "ObjModel/FigureMetaData.h"

class GraphicsFurnitureItem : public QGraphicsItem
{
public:
    explicit GraphicsFurnitureItem(QGraphicsItem *parent = 0);

private:
    FigureMetaData *figureMetaData;


};

#endif // GRAPHICSFURNITUREITEM_H
