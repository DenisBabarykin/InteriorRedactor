#ifndef SCENEREDACTORFORM_H
#define SCENEREDACTORFORM_H

#include <QMainWindow>
#include <QMap>
#include "Scene/FigureMetaData.h"
#include <QTreeWidgetItem>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include "Scene/SceneMetaData.h"

namespace Ui {
class SceneRedactorForm;
}

class SceneRedactorForm : public QMainWindow
{
    Q_OBJECT

private:
    QMap<QString, QVector<FigureMetaData> > mapCatalog;
    QList<FigureMetaData> listExObj;

    QGraphicsScene graphicsScene;

public:
    explicit SceneRedactorForm(qreal width, qreal height, QWidget *parent = 0);
    ~SceneRedactorForm();


private:
    Ui::SceneRedactorForm *ui;

    QStringList Folders(); // Список папок

private slots:
    void RefreshMapCatalog();
    void RefreshCatalog();
    void RefreshObjectList();
    void closeEvent(QCloseEvent *);
    void on_trwdgCatalog_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_btnRemoveItem_clicked();

    void on_lswdgExistingObjects_itemClicked(QListWidgetItem *item);

    void on_btnOk_clicked();

signals:
    void vecExObjChanged();
    void sceneEditedSignal(SceneMetaData sceneMetaData);
};

#endif // SCENEREDACTORFORM_H
