#ifndef LABELSCENE_H
#define LABELSCENE_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>

class LabelScene : public QLabel
{
    Q_OBJECT
public:
    explicit LabelScene(QWidget *parent = 0) : QLabel(parent) {}
    ~LabelScene() {}

    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

signals:
    void mousePressedSignal();
    void mouseReleasedSignal();
    void mouseMoveSignal(int x, int y);

};

#endif // LABELSCENE_H
