#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include "./Scene/Scene.h"
#include <QImage>
#include "./Scene/ObjModel.h"

class Painter : public QObject
{
    Q_OBJECT
protected:
    QImage *currentFrame;

protected:
    std::list<ObjModel *> *GetListFig(Scene &scene);

public:
    explicit Painter(QObject *parent = 0);
    virtual void Paint(Scene &scene) = 0;
    ~Painter() = 0;

signals:
    void PaintingDoneSignal(QImage *frame);

public slots:

};

#endif // PAINTER_H
