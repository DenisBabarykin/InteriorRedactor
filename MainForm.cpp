#include "MainForm.h"
#include "ui_MainForm.h"
#include "ObjLoader/ObjLoader.h"
#include "Scene/ObjModel.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "Exception/UnknownCommandException.h"
#include <QDesktopWidget>
#include "SceneSizesInput.h"
#include <QDebug>
#include <QImage>
#include "Facade/SingletonFacade.h"

ObjModel *pObjModel = NULL;
bool mousePressed = false;

QVector<ObjModel *> vecModel; //+

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    sceneRedactorForm = NULL;

    connect(ui->menuBtnOpenScene, SIGNAL(triggered()), this, SLOT(OpenScene()));
    connect(ui->lblScene, SIGNAL(mouseMoveSignal(int,int)), this, SLOT(MouseMove(int,int)));

    connect(SingletonFacade::GetFacade(), SIGNAL(CommandDoneSignal()), &commandController, SLOT(ExecuteNext()));
    connect(&commandController, SIGNAL(ExecutionStatusSignal(bool)), this, SLOT(statusBarUpdate(bool)));
}

void MainForm::OpenScene()
{
    /*
    QString fileName = QFileDialog::getOpenFileName(this, "Введите имя файла", "", "Files (*.obj)");

    if (fileName == "")
        return;

    if (pObjModel)
        delete pObjModel;

    ObjLoader objLoader;
    try
    {
        //objLoader.load(fileName.toStdString().c_str());
        objLoader.load(fileName.toLocal8Bit().constData());
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
    */

    sceneFilename = QFileDialog::getOpenFileName(this, "Введите имя файла", "", "Files (*.smd)");
    if (sceneFilename == "")
        return;

    sceneMetaData.LoadFromFile(sceneFilename);
    CreateNewSceneRedactor(sceneMetaData);
}

void MainForm::Draw(QVector<ObjModel *> &vec)
{
    if (ui->checkBox->isChecked())
    {
        // После появления z-буфера больше не используется
        QPixmap pic(QSize(ui->lblScene->width(), ui->lblScene->height()));
        QPainter painter(&pic);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
        painter.fillRect(0, 0, ui->lblScene->width(), ui->lblScene->height(), Qt::white);

        painter.translate(ui->lblScene->width() / 2, ui->lblScene->height() / 2);
        painter.scale(1, -1);


        for (int i = 0; i < vec.size(); ++i)
        {

            vec[i]->DrawModel(painter);
            //vec[i]->DrawModelFill(painter);
        }

        ui->lblScene->setPixmap(pic);
    }
    else
    {

        QStringList listColors = QColor::colorNames();
        ZBuffer zbuf(ui->lblScene->width(), ui->lblScene->height());
        for (int i = 0; i < vec.size(); ++i)
        {
            for (int j = 0; j < vec[i]->vecIndx.size(); ++j)
            {
                triangle tr;
                tr.a = Point3D(vec[i]->vecPnts3D[vec[i]->vecIndx[j].v1]);
                tr.b = Point3D(vec[i]->vecPnts3D[vec[i]->vecIndx[j].v2]);
                tr.c = Point3D(vec[i]->vecPnts3D[vec[i]->vecIndx[j].v3]);

                tr.a = tr.a + Point3D(ui->lblScene->width() / 2, ui->lblScene->height() / 2, 0);
                tr.b = tr.b + Point3D(ui->lblScene->width() / 2, ui->lblScene->height() / 2, 0);
                tr.c = tr.c + Point3D(ui->lblScene->width() / 2, ui->lblScene->height() / 2, 0);
                zbuf.PutTriangle(tr, QColor(listColors[(i + 3) * 3]).rgb());
            }
        }
        ui->lblScene->setPixmap(QPixmap::fromImage(zbuf.image));
    }

}

void MainForm::Shift(QVector<ObjModel *> &vec, qreal dx, qreal dy, qreal dz)
{
    for (int i = 0; i < vec.size(); ++i)
        vec[i]->Shift(dx, dy, dz);
}

void MainForm::MouseMove(int dx, int dy)
{
    static int sumX = 0, sumY = 0;

    if (!vecModel.isEmpty())
    {
        sumX += dx;
        sumY += dy;

        /*
        ObjModel tempModel = *pObjModel;
        tempModel.RotateOY(sumX);
        tempModel.RotateOX(sumY);
        Draw(tempModel);
        */

        QVector<ObjModel *> vec;
        for (int i = 0; i < vecModel.size(); ++i)
        {
            ObjModel *tempModel = new ObjModel;
            *tempModel = *(vecModel[i]);
            vec.append(tempModel);

            vec[i]->Shift(0, 0, sceneMetaData.GetSceneLengthOZ());
            vec[i]->RotateOY(sumX);
            vec[i]->RotateOX(sumY);
            vec[i]->Shift(0, 0, -sceneMetaData.GetSceneLengthOZ());
            vec[i]->Perspective();
        }
        Draw(vec);

        for (int i = 0; i < vec.size(); ++i)
            delete vec[i];
        vec.clear();
    }
}

void MainForm::CreateScene(SceneMetaData sceneMetaData)
{
    qDebug() << "Файл сцены успешно получен";
    qDebug() << "OX:" << sceneMetaData.GetSceneLengthOX() << " OZ:" << sceneMetaData.GetSceneLengthOZ();
    qDebug() << "Объектов на сцене:" << sceneMetaData.getListFig().size();

    this->sceneMetaData = sceneMetaData;
    ui->menuBtnEditScene->setEnabled(true);
    ui->menuBtnSaveScene->setEnabled(true);
    ui->menuBtnSaveAsScene->setEnabled(true);

    if (!vecModel.isEmpty())
        for (int i = 0; i < vecModel.size(); ++i)
            delete vecModel[i];
    vecModel.clear();

    for (int i = 0; i < sceneMetaData.getListFig().size(); ++i)
    {
        ObjLoader objLoader;
        qDebug() << "loading " << sceneMetaData.getListFig()[i].GetFileName();
        objLoader.load(sceneMetaData.getListFig()[i].GetFileName().toLocal8Bit().constData());
        vecModel.append(new ObjModel(objLoader));
        qDebug() << "loading completed " << sceneMetaData.getListFig()[i].GetFileName();
        vecModel[i]->Shift(sceneMetaData.getListFig()[i].GetPos().rx(), 0, sceneMetaData.getListFig()[i].GetPos().ry());
    }

    // формирование пола
    ObjModel *floor = new ObjModel;
    int dy = - 5; // чтобы исключить борьбу
    floor->vecPnts3D.append(Point3D(0, dy, 0));
    floor->vecPnts3D.append(Point3D(0, dy, sceneMetaData.GetSceneLengthOZ()));
    floor->vecPnts3D.append(Point3D(sceneMetaData.GetSceneLengthOX(), dy, sceneMetaData.GetSceneLengthOZ()));
    floor->vecPnts3D.append(Point3D(sceneMetaData.GetSceneLengthOX(), dy, 0));
    floor->vecIndx.append(FaceIndexes(0, 1, 2));
    floor->vecIndx.append(FaceIndexes(0, 2, 3));
    vecModel.append(floor);

    Shift(vecModel, -sceneMetaData.GetSceneLengthOX() / 2, 0, - 3 * sceneMetaData.GetSceneLengthOZ() / 2);
    Draw(vecModel);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_menuBtnEditScene_triggered()
{
    if (sceneRedactorForm)
        sceneRedactorForm->show();
}

void MainForm::MoveFrameToCenter()
{
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

void MainForm::on_menuBtnCreateNewScene_triggered()
{
    SceneSizesInput *sceneSizesInput = new SceneSizesInput(this);
    connect(sceneSizesInput, SIGNAL(SceneCreated(int,int)), this, SLOT(CreateNewSceneRedactor(int,int)));
    sceneSizesInput->show();
}

void MainForm::CreateNewSceneRedactor(int sceneLength, int sceneWidth)
{
    if (sceneRedactorForm)
        delete sceneRedactorForm;

    sceneRedactorForm = new SceneRedactorForm(sceneLength, sceneWidth, this);
    connect(sceneRedactorForm, SIGNAL(sceneEditedSignal(SceneMetaData)), this, SLOT(CreateScene(SceneMetaData)));
    sceneRedactorForm->show();
}

void MainForm::CreateNewSceneRedactor(SceneMetaData sceneMetaData)
{
    if (sceneRedactorForm)
        delete sceneRedactorForm;

    sceneRedactorForm = new SceneRedactorForm(sceneMetaData, this);
    connect(sceneRedactorForm, SIGNAL(sceneEditedSignal(SceneMetaData)), this, SLOT(CreateScene(SceneMetaData)));
    sceneRedactorForm->show();
}

void MainForm::on_menuBtnSaveScene_triggered()
{
    if (sceneFilename.isEmpty())
        sceneFilename = QFileDialog::getSaveFileName(this, "Введите имя файла", "", "Files (*.smd)");

    if ((sceneFilename.isEmpty()))
        return;
    else
        sceneMetaData.SaveToFile(sceneFilename);
}

void MainForm::on_menuBtnSaveAsScene_triggered()
{
    sceneFilename = QFileDialog::getSaveFileName(this, "Введите имя файла", "", "Files (*.smd)");

    if ((sceneFilename.isEmpty()))
        return;
    else
        sceneMetaData.SaveToFile(sceneFilename);
}

void MainForm::on_checkBox_clicked()
{
    MouseMove(0, 0);
}

void MainForm::statusBarUpdate(bool isExecute)
{
    if (isExecute)
        ui->statusBar->showMessage("Выполнение...");
    else
        ui->statusBar->clearMessage();
}
