#include "Painter.h"

QList<Figure *> *Painter::GetListFig(Scene &scene)
{
    return &scene.listFigWork;
}

Painter::Painter(int width, int height, QObject *parent) :
    QObject(parent), currentFrame(new QImage(width, height, QImage::Format_RGB32))
{
}

Painter::~Painter()
{
}
