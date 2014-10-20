#include "SceneRedactorForm.h"
#include "ui_SceneRedactorForm.h"
#include <QDir>

SceneRedactorForm::SceneRedactorForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneRedactorForm)
{
    ui->setupUi(this);
    connect(this, SIGNAL(vecExObjChanged()), SLOT(RefreshObjectList()));
    RefreshCatalog();
}

void SceneRedactorForm::closeEvent(QCloseEvent *)
{
    this->hide();
}

SceneRedactorForm::~SceneRedactorForm()
{
    delete ui;
}

void SceneRedactorForm::on_trwdgCatalog_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (reinterpret_cast<QTreeWidget *>(item->parent()) != ui->trwdgCatalog);
        vecExObj.append(mapCatalog[item->parent()->text(0)][item->parent()->indexOfChild(item)]);
    RefreshObjectList();
}

QStringList SceneRedactorForm::Folders()
{
    QDir dir;
    if (!dir.exists("models"))
        dir.mkdir("models");

    dir.setPath("models");
    QStringList folders = dir.entryList(QDir::Dirs | QDir::AllDirs | QDir::NoDotAndDotDot);
    if (!folders.isEmpty())
        folders.sort();
    return folders;
}

void SceneRedactorForm::RefreshMapCatalog()
{
    if (!mapCatalog.isEmpty())
        mapCatalog.clear();

    QStringList folders = Folders();
    if (folders.isEmpty())
        return;

    for (int i = 0; i < folders.size(); ++i)
    {
        QDir dir("models/" + folders.at(i));
        QStringList objFiles = dir.entryList(QStringList("*.obj"));
        QStringList previewFiles = dir.entryList(QStringList("*.png"));
        QVector<FigureMetaData> vec;

        for (int j = 0; j < objFiles.size(); ++j)
        {
            FigureMetaData figMetaData;
            figMetaData.SetName(objFiles.at(j));
            figMetaData.SetCategory(folders.at(i));
            figMetaData.LoadAndCalcMinMax();

            QString experienceStr = objFiles.at(j);
            experienceStr.replace(".obj", ".png");
            if (previewFiles.contains(experienceStr))
                figMetaData.SetPreviewStatus(true);

            vec.append(figMetaData);
        }

        mapCatalog.insert(folders.at(i), vec);
    }
}

void SceneRedactorForm::RefreshCatalog()
{
    RefreshMapCatalog();
    ui->trwdgCatalog->clear();

    for (QMap<QString, QVector<FigureMetaData> >::const_iterator it = mapCatalog.constBegin(); it != mapCatalog.constEnd(); ++it)
    {
        QTreeWidgetItem *root = new QTreeWidgetItem(ui->trwdgCatalog);
        root->setText(0, it.key());

        for (int i = 0; i < it.value().size() ; ++i)
        {
            QTreeWidgetItem *child = new QTreeWidgetItem(root);
            child->setText(0, it.value()[i].GetName());
            if (it.value()[i].HasPreview())
            {
                QString experienceStr = it.value()[i].GetName();
                experienceStr.replace(".obj", ".png");
                child->setToolTip(0, "<html><img src=\"models/" + it.value()[i].GetCategory() +
                                  "/" + experienceStr + "\"/></html>");
            }
        }
    }
}

void SceneRedactorForm::RefreshObjectList()
{
    ui->lswdgExistingObjects->clear();
    for (int i = 0; i < vecExObj.size(); ++i)
    {
        QListWidgetItem *item = new QListWidgetItem(vecExObj[i].GetName(), ui->lswdgExistingObjects);
        if (vecExObj[i].HasPreview())
        {
            QString experienceStr = vecExObj[i].GetName();
            experienceStr.replace(".obj", ".png");
            item->setToolTip("<html><img src=\"models/" + vecExObj[i].GetCategory() +
                              "/" + experienceStr + "\"/></html>");
        }
    }
}

void SceneRedactorForm::on_btnRemoveItem_clicked()
{
    if (ui->lswdgExistingObjects->currentItem() && !vecExObj.isEmpty())
        vecExObj.remove(ui->lswdgExistingObjects->row(ui->lswdgExistingObjects->currentItem()));

    emit vecExObjChanged();
}
