#include "GraphicsFurnitureItem.h"
#include <QPainter>
#include <QDebug>

GraphicsFurnitureItem::GraphicsFurnitureItem(FigureMetaData *it,
      QGraphicsItem *parent) : QGraphicsItem(parent), itFigureMetaData(it)
{
    itFigureMetaData = it;
    if (it->GetPos() == QPointF(0.0, 0.0))
        it->SetPos(it->GetPntMax() - it->GetPntMin() + QPointF(1, 1));
    this->setPos(it->GetPos());
}

QRectF GraphicsFurnitureItem::boundingRect() const
{
    //return QRectF(-GetWidth() / 2, -GetHeight() / 2, GetWidth() / 2, GetHeight() / 2);
    return QRectF(0, 0, 64, 64);
}

void GraphicsFurnitureItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*
    painter->setPen(Qt::red);
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-32, -32, 32, 32);
    */

    QPixmap *pixmap;
    if (itFigureMetaData->GetCategory() == "Журнальные столики")
    {
        pixmap = new QPixmap(":/coffee_table");
        qDebug() << itFigureMetaData;
    }
    else if (itFigureMetaData->GetCategory() == "Кровати")
        pixmap = new QPixmap(":/bed");
    else if (itFigureMetaData->GetCategory() == "Обеденные столы")
        pixmap = new QPixmap(":/table");
    else if (itFigureMetaData->GetCategory() == "Стулья")
        pixmap = new QPixmap(":/chair");
    else if (itFigureMetaData->GetCategory() == "Шкафы")
        pixmap = new QPixmap(":/cabinet");
    else
        pixmap = new QPixmap(":/question");

    painter->drawPixmap(QRectF(0, 0, 64, 64), *pixmap, QRectF(0, 0, 64, 64));

    delete pixmap;
}

qreal GraphicsFurnitureItem::GetWidth() const
{
    return itFigureMetaData->GetPntMax().x() - itFigureMetaData->GetPntMin().x();
}

qreal GraphicsFurnitureItem::GetHeight() const
{
    return itFigureMetaData->GetPntMax().y() - itFigureMetaData->GetPntMin().y();
}
