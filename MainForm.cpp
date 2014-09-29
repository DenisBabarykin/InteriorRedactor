#include "MainForm.h"
#include "ui_MainForm.h"
#include "ObjLoader/ObjLoader.h"
#include "ObjModel/ObjModel.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "ObjModel/Camera.h"

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
        pObjModel = NULL;
    }

    Draw();
}

void MainForm::Draw()
{
    QPixmap pic(QSize(ui->lblScene->width(), ui->lblScene->height()));
    QPainter painter(&pic);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.fillRect(0, 0, ui->lblScene->width(), ui->lblScene->height(), Qt::white);

    //painter.translate(0, ui->lblScene->height());
    painter.translate(ui->lblScene->width() / 2, ui->lblScene->height() / 2);
    painter.scale(1, -1);

    pObjModel->DrawModel(painter);

    ui->lblScene->setPixmap(pic);
}

MainForm::~MainForm()
{
    delete ui;
}
