#ifndef SCENESIZESINPUT_H
#define SCENESIZESINPUT_H

#include <QDialog>

namespace Ui {
class SceneSizesInput;
}

class SceneSizesInput : public QDialog
{
    Q_OBJECT

public:
    explicit SceneSizesInput(QWidget *parent = 0);
    ~SceneSizesInput();

    int GetLength();
    int GetWidth();

private:
    Ui::SceneSizesInput *ui;

    int length;
    int width;

signals:
    void SceneCreated(int length, int width);

private slots:
    void on_buttonBox_accepted();
};

#endif // SCENESIZESINPUT_H
