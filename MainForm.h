#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "Scene/ObjModel.h"
#include "SceneRedactorForm.h"
#include "Command/CommandController.h"

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
    QString sceneFilename;
    CommandController commandController;

private:
    void menuViewCheck(QAction *checkedMenuBtn);

public slots:
    void MouseMove(int dx, int dy);
    void Wheel(int delta);
    void CreateScene(SceneMetaData sceneMetaData);
    void DrawImage(QImage *image);

private slots:
    void on_menuBtnEditScene_triggered();
    void on_menuBtnCreateNewScene_triggered();

    void CreateNewSceneRedactor(int sceneLength, int sceneWidth);
    void CreateNewSceneRedactor(SceneMetaData sceneMetaData);

    void on_menuBtnSaveScene_triggered();
    void on_menuBtnSaveAsScene_triggered();

    void statusBarUpdate(bool isExecute);
    void on_menuBtnOpenScene_triggered();
    void on_menuBtnSkeletonView_triggered();
    void on_menuBtnZBufView_triggered();
    void on_menuBtnExit_triggered();
};

#endif // MAINFORM_H
