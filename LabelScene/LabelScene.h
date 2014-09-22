#ifndef LABELSCENE_H
#define LABELSCENE_H

#include <QLabel>
#include <QObject>

class LabelScene : public QLabel
{
    Q_OBJECT
public:
    explicit LabelScene(QWidget *parent = 0) : QLabel(parent) {}
    ~LabelScene() {}
};

#endif // LABELSCENE_H
