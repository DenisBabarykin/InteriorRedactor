#include "Painter.h"

std::list<ObjModel *> *Painter::GetListFig(Scene &scene)
{
    return &scene.listFigWork;
}

Painter::Painter(QObject *parent) :
    QObject(parent)
{
}
