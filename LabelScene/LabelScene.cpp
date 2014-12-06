#include "LabelScene.h"

void LabelScene::mousePressEvent(QMouseEvent *ev)
{
    mousePressed = true;
    prevX = ev->x();
    prevY = ev->y();
}

void LabelScene::mouseReleaseEvent(QMouseEvent *ev)
{
    mousePressed = false;
    prevX = ev->x();
    prevY = ev->y();
}

void LabelScene::mouseMoveEvent(QMouseEvent *ev)
{
    if (mousePressed)
        emit mouseMoveSignal(ev->x() - prevX, ev->y() - prevY);
    prevX = ev->x();
    prevY = ev->y();
}
