#include "MainForm.h"
#include "ui_MainForm.h"
#include "Figure/Figure.h"
#include "Figure/SimpleFigure.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "Exception/UnknownCommandException.h"
#include <QDesktopWidget>
#include "SceneSizesInput.h"
#include <QDebug>
#include <QImage>
#include "Facade/SingletonFacade.h"
#include "Command/CommandCreatePainter.h"
#include "Command/CommandCreateScene.h"
#include "Command/CommandDraw.h"
#include "Command/CommandRotate.h"
#include "Command/CommandSaveScene.h"
#include "Command/CommandShift.h"

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    sceneRedactorForm = NULL;
    painterType = PainterType::simpleZBuffer;

    connect(ui->lblScene, SIGNAL(mouseMoveSignal(qreal,qreal)), this, SLOT(MouseMove(qreal,qreal)));
    connect(ui->lblScene, SIGNAL(wheelSignal(int)), this, SLOT(Wheel(int)));
    connect(ui->lblScene, SIGNAL(labelResizeSignal(int,int)), this, SLOT(Resize(int,int)));

    connect(SingletonFacade::GetFacade(), SIGNAL(CommandDoneSignal()), &commandController, SLOT(ExecuteNext()), Qt::QueuedConnection);
    connect(&commandController, SIGNAL(ExecutionStatusSignal(bool)), this, SLOT(statusBarUpdate(bool)), Qt::QueuedConnection);
    connect(SingletonFacade::GetFacade(), SIGNAL(DrawImageSignal(QImage*)), this, SLOT(DrawImage(QImage*)), Qt::QueuedConnection);
}

void MainForm::MouseMove(qreal dx, qreal dy)
{
    commandController.AddCommand(new CommandRotate(dy, dx)); // dx и dy переставлены
    commandController.AddCommand(new CommandDraw());
    commandController.Execute();
}

void MainForm::Wheel(int delta)
{
    commandController.AddCommand(new CommandShift(0, 0, delta / 2));
    commandController.AddCommand(new CommandDraw());
    commandController.Execute();
}

void MainForm::Resize(int width, int height)
{
    commandController.AddCommand(new CommandCreatePainter((painterType), width, height));
    commandController.AddCommand(new CommandDraw());
    commandController.Execute();
}

void MainForm::CreateScene(SceneMetaData sceneMetaData)
{
    commandController.AddCommand(new CommandCreateScene(sceneMetaData));
    commandController.AddCommand(new CommandCreatePainter((painterType), ui->lblScene->width(), ui->lblScene->height()));
    commandController.AddCommand(new CommandDraw());
    commandController.Execute();
    ui->menuBtnSaveScene->setEnabled(true);
    ui->menuBtnSaveAsScene->setEnabled(true);
    ui->menuBtnEditScene->setEnabled(true);
}

void MainForm::DrawImage(QImage *image)
{
    ui->lblScene->setPixmap(QPixmap::fromImage(*image));
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

void MainForm::menuViewCheck(QAction *checkedMenuBtn)
{
    ui->menuBtnSkeletonView->setChecked(false);
    ui->menuBtnZBufView->setChecked(false);
    ui->menuBtnColorZBufView->setChecked(false);
    ui->menuBtnLightZBufView->setChecked(false);

    checkedMenuBtn->setChecked(true);
}

void MainForm::menuStylesheetCheck(QAction *checkedMenuBtn)
{
    ui->menuBtnNormalStylesheet->setChecked(false);
    ui->menuBtnQdarkstylesheet->setChecked(false);

    checkedMenuBtn->setChecked(true);
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
    {
        commandController.AddCommand(new CommandSaveScene(sceneFilename));
        commandController.Execute();
    }
}

void MainForm::on_menuBtnSaveAsScene_triggered()
{
    sceneFilename = QFileDialog::getSaveFileName(this, "Введите имя файла", "", "Files (*.smd)");

    if ((sceneFilename.isEmpty()))
        return;
    else
    {
        commandController.AddCommand(new CommandSaveScene(sceneFilename));
        commandController.Execute();
    }
}

void MainForm::statusBarUpdate(bool isExecute)
{
    if (isExecute)
        ui->statusBar->showMessage("Выполнение...");
    else
        ui->statusBar->clearMessage();
}

void MainForm::on_menuBtnOpenScene_triggered()
{
    sceneFilename = QFileDialog::getOpenFileName(this, "Введите имя файла", "", "Files (*.smd)");
    if (sceneFilename == "")
        return;

    SceneMetaData sceneMetaData;
    sceneMetaData.LoadFromFile(sceneFilename);

    CreateNewSceneRedactor(sceneMetaData);
}

void MainForm::on_menuBtnSkeletonView_triggered()
{
    painterType = PainterType::skeleton;
    commandController.AddCommand(new CommandCreatePainter((painterType), ui->lblScene->width(), ui->lblScene->height()));
    commandController.AddCommand(new CommandDraw());
    commandController.Execute();
    menuViewCheck(ui->menuBtnSkeletonView);
}

void MainForm::on_menuBtnZBufView_triggered()
{
    painterType = PainterType::simpleZBuffer;
    commandController.AddCommand(new CommandCreatePainter((painterType), ui->lblScene->width(), ui->lblScene->height()));
    commandController.AddCommand(new CommandDraw());
    commandController.Execute();
    menuViewCheck(ui->menuBtnZBufView);
}

void MainForm::on_menuBtnExit_triggered()
{
    this->close();
}

void MainForm::on_menuBtnNormalStylesheet_triggered()
{
    menuStylesheetCheck(ui->menuBtnNormalStylesheet);
    qApp->setStyleSheet("");
}

void MainForm::on_menuBtnQdarkstylesheet_triggered()
{
    QFile f(":qdarkstyle/style.qss");
    if (f.exists())
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        menuStylesheetCheck(ui->menuBtnQdarkstylesheet);
        qApp->setStyleSheet(ts.readAll());
    }
    else
    {
        ui->menuBtnQdarkstylesheet->setChecked(false);
        QMessageBox::warning(this, "Ошибка применения стиля", "Выбранный стиль не может быть применён, так как не был найден файл стилей.");
    }
}

void MainForm::on_menuBtnFullscreen_triggered()
{
    if (ui->menuBtnFullscreen->isChecked())
        this->showFullScreen();
    else
        this->showNormal();
}

void MainForm::on_menuBtnColorZBufView_triggered()
{
    painterType = PainterType::colorSimpleZBuffer;
    commandController.AddCommand(new CommandCreatePainter((painterType), ui->lblScene->width(), ui->lblScene->height()));
    commandController.AddCommand(new CommandDraw());
    commandController.Execute();
    menuViewCheck(ui->menuBtnColorZBufView);
}

void MainForm::on_menuBtnLightZBufView_triggered()
{
    painterType = PainterType::simpleLightZBuffer;
    commandController.AddCommand(new CommandCreatePainter((painterType), ui->lblScene->width(), ui->lblScene->height()));
    commandController.AddCommand(new CommandDraw());
    commandController.Execute();
    menuViewCheck(ui->menuBtnLightZBufView);
}
