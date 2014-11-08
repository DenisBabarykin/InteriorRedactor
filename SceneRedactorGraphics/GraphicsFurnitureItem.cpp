#include "GraphicsFurnitureItem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>

GraphicsFurnitureItem::GraphicsFurnitureItem(FigureMetaData *it,
      QGraphicsItem *parent) : QGraphicsItem(parent), itFigureMetaData(it)
{
    setFlag(ItemSendsGeometryChanges);

    itFigureMetaData = it;
    /*if (it->GetPos() == QPointF(0.0, 0.0))
        it->SetPos(it->GetPntMax() - it->GetPntMin() + QPointF(1, 1));*/
    it->SetPos(66, 66);
    this->setPos(it->GetPos());
}

QRectF GraphicsFurnitureItem::boundingRect() const
{
    //return QRectF(-GetWidth() / 2, -GetHeight() / 2, GetWidth() / 2, GetHeight() / 2);
    return QRectF(-32, -32, 64.5, 64.5);
}

void GraphicsFurnitureItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*
    painter->setPen(Qt::red);
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-32, -32, 32, 32);
    */

    //qDebug() << itFigureMetaData;
    //qDebug() << itFigureMetaData->GetPos();
    QPixmap *pixmap;// = new QPixmap(":/bed");
    if (itFigureMetaData->GetCategory() == "Журнальные столики")
        pixmap = new QPixmap(":/coffee_table");
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


    painter->drawPixmap(QRectF(-32, -32, 64, 64), *pixmap, QRectF(0, 0, 64, 64));

    delete pixmap;
}

qreal GraphicsFurnitureItem::GetWidth() const
{
    //return itFigureMetaData->GetPntMax().x() - itFigureMetaData->GetPntMin().x();
    return 64;
}

qreal GraphicsFurnitureItem::GetHeight() const
{
    //return itFigureMetaData->GetPntMax().y() - itFigureMetaData->GetPntMin().y();
    return 64;
}

QVariant GraphicsFurnitureItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        //if (!rect.contains(newPos))
        if (newPos.x() - GetWidth()/2 < rect.left() || newPos.y() - GetHeight()/2 < rect.top() ||
                newPos.x() + GetWidth()/2 > rect.right() || newPos.y() + GetHeight()/2 > rect.bottom())
        {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right() - GetWidth()/2, qMax(newPos.x(), rect.left() + GetWidth()/2)));
            newPos.setY(qMin(rect.bottom() - GetHeight()/2, qMax(newPos.y(), rect.top() + GetHeight()/2)));
            return newPos;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
