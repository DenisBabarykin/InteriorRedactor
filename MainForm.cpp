#include "MainForm.h"
#include "ui_MainForm.h"
#include "ObjLoader/ObjLoader.h"
#include "ObjModel/ObjModel.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>

ObjModel *pObjModel = NULL;

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    connect(ui->menuBtnOpenScene, SIGNAL(triggered()), this, SLOT(OpenScene()));
}

void MainForm::OpenScene()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Введите имя файла", "", "Files (*.obj)");

    if (fileName == "")
        return;

    if (pObjModel)
        delete pObjModel;

    ObjLoader objLoader;
    objLoader.load(fileName.toStdString().c_str());

    try
    {
        pObjModel = new ObjModel(objLoader);
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
