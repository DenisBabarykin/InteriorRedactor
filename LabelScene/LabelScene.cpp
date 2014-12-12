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
    static qreal sumX = 0, sumY = 0;
    static int n = 0;
    const qreal del = 1.5;
    if (mousePressed)
    {
        ++n;
        sumX += ev->x() - prevX;
        sumY += ev->y() - prevY;
        if (n == 3)  // n-ый заход
        {
            emit mouseMoveSignal(sumX / del, sumY / del);
            sumX = sumY = 0.0;
            n = 0;
        }
    }
    prevX = ev->x();
    prevY = ev->y();
}

void LabelScene::wheelEvent(QWheelEvent *ev)
{
    emit wheelSignal(ev->delta());
}
