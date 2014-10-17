#ifndef SCENEREDACTORFORM_H
#define SCENEREDACTORFORM_H

#include <QMainWindow>
#include <QMap>
#include "ObjModel/FigureMetaData.h"
#include <QTreeWidgetItem>

namespace Ui {
class SceneRedactorForm;
}

class SceneRedactorForm : public QMainWindow
{
    Q_OBJECT

private:
    QMap<QString, QVector<FigureMetaData> > mapCatalog;
    QVector<FigureMetaData> vecExObj;

public:
    explicit SceneRedactorForm(QWidget *parent = 0);
    ~SceneRedactorForm();
    void RefreshCatalog();
    void RefreshObjectList();

private:
    Ui::SceneRedactorForm *ui;

    QStringList Folders(); // Список папок
    void RefreshMapCatalog();

private slots:
    void closeEvent(QCloseEvent *);
    void on_trwdgCatalog_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_btnRemoveItem_clicked();
};

#endif // SCENEREDACTORFORM_H
