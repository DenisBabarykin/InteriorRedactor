#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "Figure/SimpleFigure.h"
#include "SceneRedactorForm.h"
#include "Command/CommandController.h"
#include "Painter/PainterType.h"

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private:
    Ui::MainForm *ui;
    SceneRedactorForm *sceneRedactorForm;
    QString sceneFilename;
    CommandController commandController;
    PainterType::PainterType painterType;

private:
    void menuViewCheck(QAction *checkedMenuBtn);
    void menuStylesheetCheck(QAction *checkedMenuBtn);

public slots:
    void MouseMove(qreal dx, qreal dy);
    void Wheel(int delta);
    void Resize(int width, int height);
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
    void on_menuBtnNormalStylesheet_triggered();
    void on_menuBtnQdarkstylesheet_triggered();
    void on_menuBtnFullscreen_triggered();
    void on_menuBtnColorZBufView_triggered();
    void on_menuBtnLightZBufView_triggered();
};

#endif // MAINFORM_H
