/********************************************************************************
** Form generated from reading UI file 'MainForm.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "LabelScene/LabelScene.h"

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QAction *menuBtnCreateNewScene;
    QAction *menuBtnOpenScene;
    QAction *menuBtnSaveScene;
    QAction *menuBtnSaveAsScene;
    QAction *menuBtnCloseScene;
    QWidget *centralWidget;
    QGroupBox *grbxSceneRedactor;
    QTreeWidget *trwdgCatalog;
    QGraphicsView *grvwScheme;
    QGroupBox *grbxSceneViewer;
    LabelScene *lblScene;
    QGroupBox *grbxCamera;
    QGroupBox *grbxCameraShift;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *ledtCameraShiftForward;
    QLineEdit *ledtCameraShiftBackward;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *ledtCameraShiftUp;
    QLineEdit *ledtCameraShiftDown;
    QLineEdit *ledtCameraShiftLeft;
    QLineEdit *ledtCameraShiftRight;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblCameraShiftUp;
    QLabel *lblCameraShiftDown;
    QLabel *lblCameraShiftLeft;
    QLabel *lblCameraShiftRight;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblCameraShiftForward;
    QLabel *lblCameraShiftForward_2;
    QGroupBox *grbxCameraRotate;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *ledtCameraRotateOX;
    QLineEdit *ledtCameraRotateOY;
    QLineEdit *ledtCameraRotateOZ;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_6;
    QLabel *lblCameraRotateOX;
    QLabel *lblCameraRotateOX_2;
    QLabel *lblCameraRotateOX_3;
    QPushButton *btnCameraApply;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QStringLiteral("MainForm"));
        MainForm->resize(1366, 768);
        menuBtnCreateNewScene = new QAction(MainForm);
        menuBtnCreateNewScene->setObjectName(QStringLiteral("menuBtnCreateNewScene"));
        menuBtnOpenScene = new QAction(MainForm);
        menuBtnOpenScene->setObjectName(QStringLiteral("menuBtnOpenScene"));
        menuBtnSaveScene = new QAction(MainForm);
        menuBtnSaveScene->setObjectName(QStringLiteral("menuBtnSaveScene"));
        menuBtnSaveAsScene = new QAction(MainForm);
        menuBtnSaveAsScene->setObjectName(QStringLiteral("menuBtnSaveAsScene"));
        menuBtnCloseScene = new QAction(MainForm);
        menuBtnCloseScene->setObjectName(QStringLiteral("menuBtnCloseScene"));
        centralWidget = new QWidget(MainForm);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        grbxSceneRedactor = new QGroupBox(centralWidget);
        grbxSceneRedactor->setObjectName(QStringLiteral("grbxSceneRedactor"));
        grbxSceneRedactor->setGeometry(QRect(10, 0, 661, 701));
        trwdgCatalog = new QTreeWidget(grbxSceneRedactor);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("\320\232\320\260\321\202\320\260\320\273\320\276\320\263"));
        trwdgCatalog->setHeaderItem(__qtreewidgetitem);
        trwdgCatalog->setObjectName(QStringLiteral("trwdgCatalog"));
        trwdgCatalog->setGeometry(QRect(10, 20, 161, 671));
        trwdgCatalog->setHeaderHidden(false);
        grvwScheme = new QGraphicsView(grbxSceneRedactor);
        grvwScheme->setObjectName(QStringLiteral("grvwScheme"));
        grvwScheme->setGeometry(QRect(180, 20, 470, 470));
        grbxSceneViewer = new QGroupBox(centralWidget);
        grbxSceneViewer->setObjectName(QStringLiteral("grbxSceneViewer"));
        grbxSceneViewer->setGeometry(QRect(680, 0, 681, 701));
        lblScene = new LabelScene(grbxSceneViewer);
        lblScene->setObjectName(QStringLiteral("lblScene"));
        lblScene->setGeometry(QRect(10, 20, 662, 521));
        lblScene->setFrameShape(QFrame::Box);
        grbxCamera = new QGroupBox(grbxSceneViewer);
        grbxCamera->setObjectName(QStringLiteral("grbxCamera"));
        grbxCamera->setGeometry(QRect(10, 540, 661, 151));
        grbxCameraShift = new QGroupBox(grbxCamera);
        grbxCameraShift->setObjectName(QStringLiteral("grbxCameraShift"));
        grbxCameraShift->setGeometry(QRect(10, 15, 231, 131));
        layoutWidget = new QWidget(grbxCameraShift);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(128, 20, 52, 48));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        ledtCameraShiftForward = new QLineEdit(layoutWidget);
        ledtCameraShiftForward->setObjectName(QStringLiteral("ledtCameraShiftForward"));

        verticalLayout_3->addWidget(ledtCameraShiftForward);

        ledtCameraShiftBackward = new QLineEdit(layoutWidget);
        ledtCameraShiftBackward->setObjectName(QStringLiteral("ledtCameraShiftBackward"));

        verticalLayout_3->addWidget(ledtCameraShiftBackward);

        layoutWidget1 = new QWidget(grbxCameraShift);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 54, 101));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ledtCameraShiftUp = new QLineEdit(layoutWidget1);
        ledtCameraShiftUp->setObjectName(QStringLiteral("ledtCameraShiftUp"));

        verticalLayout->addWidget(ledtCameraShiftUp);

        ledtCameraShiftDown = new QLineEdit(layoutWidget1);
        ledtCameraShiftDown->setObjectName(QStringLiteral("ledtCameraShiftDown"));

        verticalLayout->addWidget(ledtCameraShiftDown);

        ledtCameraShiftLeft = new QLineEdit(layoutWidget1);
        ledtCameraShiftLeft->setObjectName(QStringLiteral("ledtCameraShiftLeft"));

        verticalLayout->addWidget(ledtCameraShiftLeft);

        ledtCameraShiftRight = new QLineEdit(layoutWidget1);
        ledtCameraShiftRight->setObjectName(QStringLiteral("ledtCameraShiftRight"));

        verticalLayout->addWidget(ledtCameraShiftRight);

        layoutWidget2 = new QWidget(grbxCameraShift);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(70, 20, 38, 101));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblCameraShiftUp = new QLabel(layoutWidget2);
        lblCameraShiftUp->setObjectName(QStringLiteral("lblCameraShiftUp"));

        verticalLayout_2->addWidget(lblCameraShiftUp);

        lblCameraShiftDown = new QLabel(layoutWidget2);
        lblCameraShiftDown->setObjectName(QStringLiteral("lblCameraShiftDown"));

        verticalLayout_2->addWidget(lblCameraShiftDown);

        lblCameraShiftLeft = new QLabel(layoutWidget2);
        lblCameraShiftLeft->setObjectName(QStringLiteral("lblCameraShiftLeft"));

        verticalLayout_2->addWidget(lblCameraShiftLeft);

        lblCameraShiftRight = new QLabel(layoutWidget2);
        lblCameraShiftRight->setObjectName(QStringLiteral("lblCameraShiftRight"));

        verticalLayout_2->addWidget(lblCameraShiftRight);

        layoutWidget3 = new QWidget(grbxCameraShift);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(184, 20, 39, 51));
        verticalLayout_4 = new QVBoxLayout(layoutWidget3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        lblCameraShiftForward = new QLabel(layoutWidget3);
        lblCameraShiftForward->setObjectName(QStringLiteral("lblCameraShiftForward"));

        verticalLayout_4->addWidget(lblCameraShiftForward);

        lblCameraShiftForward_2 = new QLabel(layoutWidget3);
        lblCameraShiftForward_2->setObjectName(QStringLiteral("lblCameraShiftForward_2"));

        verticalLayout_4->addWidget(lblCameraShiftForward_2);

        grbxCameraRotate = new QGroupBox(grbxCamera);
        grbxCameraRotate->setObjectName(QStringLiteral("grbxCameraRotate"));
        grbxCameraRotate->setGeometry(QRect(248, 15, 151, 101));
        layoutWidget4 = new QWidget(grbxCameraRotate);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 20, 52, 74));
        verticalLayout_5 = new QVBoxLayout(layoutWidget4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        ledtCameraRotateOX = new QLineEdit(layoutWidget4);
        ledtCameraRotateOX->setObjectName(QStringLiteral("ledtCameraRotateOX"));

        verticalLayout_5->addWidget(ledtCameraRotateOX);

        ledtCameraRotateOY = new QLineEdit(layoutWidget4);
        ledtCameraRotateOY->setObjectName(QStringLiteral("ledtCameraRotateOY"));

        verticalLayout_5->addWidget(ledtCameraRotateOY);

        ledtCameraRotateOZ = new QLineEdit(layoutWidget4);
        ledtCameraRotateOZ->setObjectName(QStringLiteral("ledtCameraRotateOZ"));

        verticalLayout_5->addWidget(ledtCameraRotateOZ);

        layoutWidget5 = new QWidget(grbxCameraRotate);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(68, 22, 74, 71));
        verticalLayout_6 = new QVBoxLayout(layoutWidget5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        lblCameraRotateOX = new QLabel(layoutWidget5);
        lblCameraRotateOX->setObjectName(QStringLiteral("lblCameraRotateOX"));

        verticalLayout_6->addWidget(lblCameraRotateOX);

        lblCameraRotateOX_2 = new QLabel(layoutWidget5);
        lblCameraRotateOX_2->setObjectName(QStringLiteral("lblCameraRotateOX_2"));

        verticalLayout_6->addWidget(lblCameraRotateOX_2);

        lblCameraRotateOX_3 = new QLabel(layoutWidget5);
        lblCameraRotateOX_3->setObjectName(QStringLiteral("lblCameraRotateOX_3"));

        verticalLayout_6->addWidget(lblCameraRotateOX_3);

        btnCameraApply = new QPushButton(grbxCamera);
        btnCameraApply->setObjectName(QStringLiteral("btnCameraApply"));
        btnCameraApply->setGeometry(QRect(280, 120, 75, 23));
        MainForm->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainForm);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1366, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainForm->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainForm);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainForm->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainForm);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainForm->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(menuBtnCreateNewScene);
        menu->addAction(menuBtnOpenScene);
        menu->addSeparator();
        menu->addAction(menuBtnSaveScene);
        menu->addAction(menuBtnSaveAsScene);
        menu->addSeparator();
        menu->addAction(menuBtnCloseScene);
        mainToolBar->addAction(menuBtnCreateNewScene);
        mainToolBar->addAction(menuBtnOpenScene);
        mainToolBar->addSeparator();
        mainToolBar->addAction(menuBtnSaveScene);
        mainToolBar->addAction(menuBtnSaveAsScene);
        mainToolBar->addSeparator();
        mainToolBar->addAction(menuBtnCloseScene);

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\270\320\275\321\202\320\265\321\200\321\214\320\265\321\200\320\260", 0));
        menuBtnCreateNewScene->setText(QApplication::translate("MainForm", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\201\321\206\320\265\320\275\321\203", 0));
        menuBtnCreateNewScene->setShortcut(QApplication::translate("MainForm", "Ctrl+N", 0));
        menuBtnOpenScene->setText(QApplication::translate("MainForm", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\201\321\206\320\265\320\275\321\203", 0));
        menuBtnOpenScene->setShortcut(QApplication::translate("MainForm", "Ctrl+O", 0));
        menuBtnSaveScene->setText(QApplication::translate("MainForm", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        menuBtnSaveScene->setShortcut(QApplication::translate("MainForm", "Ctrl+S", 0));
        menuBtnSaveAsScene->setText(QApplication::translate("MainForm", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272...", 0));
        menuBtnCloseScene->setText(QApplication::translate("MainForm", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0));
        menuBtnCloseScene->setShortcut(QApplication::translate("MainForm", "Ctrl+W", 0));
        grbxSceneRedactor->setTitle(QApplication::translate("MainForm", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \321\201\321\206\320\265\320\275\321\213", 0));
        grbxSceneViewer->setTitle(QApplication::translate("MainForm", "\320\236\320\261\320\276\320\267\321\200\320\265\320\262\320\260\321\202\320\265\320\273\321\214 \321\201\321\206\320\265\320\275\321\213", 0));
        lblScene->setText(QString());
        grbxCamera->setTitle(QApplication::translate("MainForm", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\260\320\274\320\265\321\200\320\276\320\271", 0));
        grbxCameraShift->setTitle(QApplication::translate("MainForm", "\320\241\320\264\320\262\320\270\320\263", 0));
        lblCameraShiftUp->setText(QApplication::translate("MainForm", "\320\222\320\262\320\265\321\200\321\205", 0));
        lblCameraShiftDown->setText(QApplication::translate("MainForm", "\320\222\320\275\320\270\320\267", 0));
        lblCameraShiftLeft->setText(QApplication::translate("MainForm", "\320\222\320\273\320\265\320\262\320\276", 0));
        lblCameraShiftRight->setText(QApplication::translate("MainForm", "\320\222\320\277\321\200\320\260\320\262\320\276", 0));
        lblCameraShiftForward->setText(QApplication::translate("MainForm", "\320\222\320\277\320\265\321\200\321\221\320\264", 0));
        lblCameraShiftForward_2->setText(QApplication::translate("MainForm", "\320\235\320\260\320\267\320\260\320\264", 0));
        grbxCameraRotate->setTitle(QApplication::translate("MainForm", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202", 0));
        lblCameraRotateOX->setText(QApplication::translate("MainForm", "\320\222\320\276\320\272\321\200\321\203\320\263 \320\276\321\201\320\270 OX", 0));
        lblCameraRotateOX_2->setText(QApplication::translate("MainForm", "\320\222\320\276\320\272\321\200\321\203\320\263 \320\276\321\201\320\270 OY", 0));
        lblCameraRotateOX_3->setText(QApplication::translate("MainForm", "\320\222\320\276\320\272\321\200\321\203\320\263 \320\276\321\201\320\270 OZ", 0));
        btnCameraApply->setText(QApplication::translate("MainForm", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", 0));
        menu->setTitle(QApplication::translate("MainForm", "\320\244\320\260\320\271\320\273", 0));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
