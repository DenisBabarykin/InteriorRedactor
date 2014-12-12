#include "Skeleton.h"

Skeleton::Skeleton(int height, int width, QObject *parent)
    : Painter(height, width, parent)
{
}

void Skeleton::Paint(Scene &scene)
{
    QPainter painter(currentFrame);
    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.fillRect(0, 0, currentFrame->width(), currentFrame->height(), Qt::black);

    painter.translate(currentFrame->width() / 2, currentFrame->height() / 2);
    painter.scale(1, -1);


    for (int i = 0; i < GetListFig(scene)->size(); ++i)
    {
        (*GetListFig(scene))[i]->DrawModel(painter);
    }

    emit PaintingDoneSignal(currentFrame);
}

Skeleton::~Skeleton()
{

}
