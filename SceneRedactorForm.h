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

 signals:
    void vecExObjChanged();
};

#endif // SCENEREDACTORFORM_H
