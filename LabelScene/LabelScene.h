#ifndef LABELSCENE_H
#define LABELSCENE_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>

class LabelScene : public QLabel
{
    Q_OBJECT
public:
    explicit LabelScene(QWidget *parent = 0) : QLabel(parent) { mousePressed = false;}
    ~LabelScene() {}

    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);
    void resizeEvent(QResizeEvent *ev);

private:
    int prevX, prevY;
    bool mousePressed;

signals:
    void mouseMoveSignal(qreal dx, qreal dy);
    void wheelSignal(int delta);
    void labelResizeSignal(int width, int height);

};

#endif // LABELSCENE_H
