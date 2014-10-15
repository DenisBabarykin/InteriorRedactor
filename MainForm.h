#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "ObjModel/ObjModel.h"
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

private:
    Ui::MainForm *ui;
    SceneRedactorForm *sceneRedactorForm;

private:
    void Draw(ObjModel &objModel);

public slots:
    void OpenScene();
    void MouseMove(int dx, int dy);

private slots:
    void on_menuBtnEditScene_triggered();
};

#endif // MAINFORM_H
