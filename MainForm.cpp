#include "MainForm.h"
#include "ui_MainForm.h"
#include "ObjLoader/ObjLoader.h"
#include "ObjModel/ObjModel.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    ObjLoader objLoader;
    objLoader.load("office_chair.obj");

    try
    {
        ObjModel objModel(objLoader);
    }
    catch(const char *exMsg)
    {
        QMessageBox::warning(this, "Exception", QString(exMsg));
    }
}

MainForm::~MainForm()
{
    delete ui;
}
