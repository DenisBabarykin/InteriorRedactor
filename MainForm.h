#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "ObjModel/ObjModel.h"

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

private:
    void Draw(ObjModel &objModel);

public slots:
    void OpenScene();
    void MousePress();
    void MouseRelease();
    void MouseMove(int x, int y);

};

#endif // MAINFORM_H
