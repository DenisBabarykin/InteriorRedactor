#include "MainForm.h"
#include "ui_MainForm.h"
#include "ObjLoader/ObjLoader.h"
#include "ObjModel/ObjModel.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "ObjModel/Camera.h"

ObjModel *pObjModel = NULL;
bool mousePressed = false;

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    connect(ui->menuBtnOpenScene, SIGNAL(triggered()), this, SLOT(OpenScene()));
    connect(ui->lblScene, SIGNAL(mousePressedSignal()), this, SLOT(MousePress()));
    connect(ui->lblScene, SIGNAL(mouseReleasedSignal()), this, SLOT(MouseRelease()));
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

void MainForm::MouseMove(int x, int y)
{
    static int prevX = x, prevY = y;
    static int sumX = 0, sumY = 0;

    if (mousePressed && pObjModel)
    {
        ObjModel tempModel = *pObjModel;
        sumX -= x - prevX;
        sumY -= y - prevY;
        tempModel.RotateOY(sumX);
        tempModel.RotateOX(sumY);
        Draw(tempModel);
    }

    prevX = x;
    prevY = y;
}

void MainForm::MousePress()
{
    mousePressed = true;
}

void MainForm::MouseRelease()
{
    mousePressed = false;
}

MainForm::~MainForm()
{
    delete ui;
}
