#ifndef SCENESIZESINPUT_H
#define SCENESIZESINPUT_H

#include <QDialog>
#include <QIntValidator>

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

    QIntValidator *sizesValidator;

signals:
    void SceneCreated(int length, int width);

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
};

#endif // SCENESIZESINPUT_H
