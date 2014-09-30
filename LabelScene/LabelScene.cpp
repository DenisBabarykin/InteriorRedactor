#include "LabelScene.h"

void LabelScene::mousePressEvent(QMouseEvent *ev)
{
    emit mousePressedSignal();
}

void LabelScene::mouseReleaseEvent(QMouseEvent *ev)
{
    emit mouseReleasedSignal();
}

void LabelScene::mouseMoveEvent(QMouseEvent *ev)
{
    emit mouseMoveSignal(ev->x(), ev->y());
}
