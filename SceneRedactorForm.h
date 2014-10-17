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

public:
    explicit SceneRedactorForm(QWidget *parent = 0);
    ~SceneRedactorForm();
    void RefreshCatalog();

private:
    Ui::SceneRedactorForm *ui;

    QStringList Folders(); // Список папок
    void RefreshMapCatalog();

private slots:
    void closeEvent(QCloseEvent *);
    void on_trwdgCatalog_itemDoubleClicked(QTreeWidgetItem *item, int column);
};

#endif // SCENEREDACTORFORM_H
