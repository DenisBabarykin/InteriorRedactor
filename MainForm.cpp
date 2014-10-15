#include "MainForm.h"
#include "ui_MainForm.h"
#include "ObjLoader/ObjLoader.h"
#include "ObjModel/ObjModel.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "ObjModel/Camera.h"
#include "Exception/UnknownCommandException.h"

ObjModel *pObjModel = NULL;
bool mousePressed = false;

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    sceneRedactorForm = new SceneRedactorForm(this);

    connect(ui->menuBtnOpenScene, SIGNAL(triggered()), this, SLOT(OpenScene()));
    connect(ui->lblScene, SIGNAL(mouseMoveSignal(int,int)), this, SLOT(MouseMove(int,int)));
}

void MainForm::OpenScene()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Введите имя файла", "", "Files (*.obj)");

    if (fileName == "")
        return;

    if (pObjModel)
        delete pObjModel;

    ObjLoader objLoader;
    try
    {
        objLoader.load(fileName.toStdString().c_str());
    }
    catch(UnknownCommandException &ex)
    {
        QMessageBox::warning(this, ex.GetType(), ex.GetMessage() + ex.GetDebugMessage());
        return ;
    }
    catch(const char *exMsg)
    {
        QMessageBox::warning(this, "Exception", QString(exMsg));
        return ;
        pObjModel = NULL;
    }

    try
    {
        pObjModel = new ObjModel(objLoader);
    }
    catch(const char *exMsg)
    {
        QMessageBox::warning(this, "Exception", QString(exMsg));
        pObjModel = NULL;
    }

    Draw(*pObjModel);
}

void MainForm::Draw(ObjModel &objModel)
{
    QPixmap pic(QSize(ui->lblScene->width(), ui->lblScene->height()));
    QPainter painter(&pic);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.fillRect(0, 0, ui->lblScene->width(), ui->lblScene->height(), Qt::white);

    painter.translate(ui->lblScene->width() / 2, ui->lblScene->height() / 2);
    painter.scale(1, -1);

    objModel.DrawModel(painter);

    ui->lblScene->setPixmap(pic);
}

void MainForm::MouseMove(int dx, int dy)
{
    static int sumX = 0, sumY = 0;

    if (pObjModel)
    {
        ObjModel tempModel = *pObjModel;
        sumX -= dx;
        sumY -= dy;
        tempModel.RotateOY(sumX);
        tempModel.RotateOX(sumY);
        Draw(tempModel);
    }
}


MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_menuBtnEditScene_triggered()
{
    sceneRedactorForm->show();
}
