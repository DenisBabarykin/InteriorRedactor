#ifndef LABELSCENE_H
#define LABELSCENE_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>

class LabelScene : public QLabel
{
    Q_OBJECT
public:
    explicit LabelScene(QWidget *parent = 0) : QLabel(parent) { mousePressed = false;}
    ~LabelScene() {}

    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private:
    int prevX, prevY;
    bool mousePressed;

signals:
    void mouseMoveSignal(int dx, int dy);

};

#endif // LABELSCENE_H
