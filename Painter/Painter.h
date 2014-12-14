#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include "./Scene/Scene.h"
#include <QImage>
#include "./Figure/SimpleFigure.h"

class Painter : public QObject
{
    Q_OBJECT
protected:
    QImage *currentFrame;

protected:
    QList<Figure *> *GetListFig(Scene &scene);

public:
    explicit Painter(int width, int height, QObject *parent = 0);
    virtual void Paint(Scene &scene) = 0;
    ~Painter();

signals:
    void PaintingDoneSignal(QImage *frame);

public slots:

};

#endif // PAINTER_H
