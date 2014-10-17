#include "SceneRedactorForm.h"
#include "ui_SceneRedactorForm.h"
#include <QDir>

SceneRedactorForm::SceneRedactorForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneRedactorForm)
{
    ui->setupUi(this);
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
        QStringList files = dir.entryList(QStringList("*.obj"));
        QVector<FigureMetaData> vec;

        for (int j = 0; j < files.size(); ++j)
        {
            FigureMetaData figMetaData;
            figMetaData.SetName(files.at(j));
            figMetaData.SetCategory(folders.at(i));
            figMetaData.LoadAndCalcMinMax();

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
        }
    }
}
