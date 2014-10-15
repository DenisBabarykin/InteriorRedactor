#include "SceneRedactorForm.h"
#include "ui_SceneRedactorForm.h"

SceneRedactorForm::SceneRedactorForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneRedactorForm)
{
    ui->setupUi(this);
}

SceneRedactorForm::~SceneRedactorForm()
{
    delete ui;
}
