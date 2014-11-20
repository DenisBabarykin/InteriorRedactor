#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "Scene/ObjModel.h"
#include "SceneRedactorForm.h"

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    void MoveFrameToCenter();

private:
    Ui::MainForm *ui;
    SceneRedactorForm *sceneRedactorForm;
    SceneMetaData sceneMetaData;
    QString sceneFilename;

private:
    void Draw(QVector<ObjModel *> &vec);
    void Shift(QVector<ObjModel *> &vec, qreal dx, qreal dy, qreal dz);

public slots:
    void OpenScene();
    void MouseMove(int dx, int dy);
    void CreateScene(SceneMetaData sceneMetaData);

private slots:
    void on_menuBtnEditScene_triggered();
    void on_menuBtnCreateNewScene_triggered();

    void CreateNewSceneRedactor(int sceneLength, int sceneWidth);
    void CreateNewSceneRedactor(SceneMetaData sceneMetaData);

    void on_menuBtnSaveScene_triggered();
    void on_menuBtnSaveAsScene_triggered();
};

#endif // MAINFORM_H
