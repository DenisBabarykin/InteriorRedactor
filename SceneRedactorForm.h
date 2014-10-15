#ifndef SCENEREDACTORFORM_H
#define SCENEREDACTORFORM_H

#include <QMainWindow>

namespace Ui {
class SceneRedactorForm;
}

class SceneRedactorForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit SceneRedactorForm(QWidget *parent = 0);
    ~SceneRedactorForm();

private:
    Ui::SceneRedactorForm *ui;
};

#endif // SCENEREDACTORFORM_H
