#include "SceneRedactorForm.h"
#include "ui_SceneRedactorForm.h"
#include <QDir>
#include "SceneRedactorGraphics/GraphicsFurnitureItem.h"
#include <QDebug>
#include <typeinfo>

SceneRedactorForm::SceneRedactorForm(qreal width, qreal height, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SceneRedactorForm)
{
    ui->setupUi(this);
    connect(this, SIGNAL(vecExObjChanged()), SLOT(RefreshObjectList()));
    RefreshCatalog();
    graphicsScene.setSceneRect(0, 0, width, height);
    ui->grvwScheme->setScene(&graphicsScene);

    //QBrush blueBrush(Qt::gray);
    QPen outlinePen(Qt::darkGray);
    outlinePen.setWidth(10);

    QGraphicsRectItem *floorItem = new QGraphicsRectItem(0, 0, width, height);
    floorItem->setPen(outlinePen);
    floorItem->setBrush(QBrush(Qt::lightGray));
    graphicsScene.addItem(floorItem);

    QList<QGraphicsItem *> list1 = graphicsScene.items();
    list1.clear();
}

SceneRedactorForm::SceneRedactorForm(SceneMetaData sceneMetaData, QWidget *parent) :
    SceneRedactorForm(sceneMetaData.GetSceneLengthOX(), sceneMetaData.GetSceneLengthOZ(), parent)
{
    for (int i = 0; i < sceneMetaData.getListFig().size(); ++i)
    {
        listExObj.push_back(new FigureMetaData());
        *listExObj[i] = *sceneMetaData.getListFig()[i];
    }

    for (int i = 0; i < listExObj.size(); ++i)
    {
        GraphicsFurnitureItem *graphicsFurnitureItem = new GraphicsFurnitureItem(listExObj[i]);
        graphicsFurnitureItem->setFlag(QGraphicsItem::ItemIsMovable);
        graphicsScene.addItem(graphicsFurnitureItem);
    }

    graphicsScene.clearSelection();
    RefreshObjectList();

    QList<QGraphicsItem *> list2 = graphicsScene.items();
    list2.clear();
}

void SceneRedactorForm::closeEvent(QCloseEvent *)
{
    hide();
}

SceneRedactorForm::~SceneRedactorForm()
{
    for (int i = 0; i < listExObj.size(); ++i)
        delete listExObj[i];
    listExObj.clear();
    delete ui;
}

void SceneRedactorForm::on_trwdgCatalog_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (item->parent())
    {
        listExObj.push_back(new FigureMetaData());
        *listExObj[listExObj.size()-1] = mapCatalog[item->parent()->text(0)][item->parent()->indexOfChild(item)];
        //listExObj.append(mapCatalog[item->parent()->text(0)][item->parent()->indexOfChild(item)]);

        GraphicsFurnitureItem *graphicsFurnitureItem = new GraphicsFurnitureItem(listExObj[listExObj.size() - 1]);
        graphicsFurnitureItem->setFlag(QGraphicsItem::ItemIsMovable);
        graphicsScene.clearSelection();
        graphicsFurnitureItem->setSelected(true);
        graphicsScene.addItem(graphicsFurnitureItem);

        RefreshObjectList();
    }
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
    for (int i = 0; i < listExObj.size(); ++i)
    {
        QListWidgetItem *item = new QListWidgetItem(listExObj[i]->GetName(), ui->lswdgExistingObjects);
        if (listExObj[i]->HasPreview())
        {
            QString experienceStr = listExObj[i]->GetName();
            experienceStr.replace(".obj", ".png");
            item->setToolTip("<html><img src=\"models/" + listExObj[i]->GetCategory() +
                              "/" + experienceStr + "\"/></html>");
        }
    }
}

void SceneRedactorForm::on_btnRemoveItem_clicked()
{
    if (ui->lswdgExistingObjects->currentItem() && !listExObj.isEmpty())
    {
        int ind = ui->lswdgExistingObjects->row(ui->lswdgExistingObjects->currentItem());

        QList<QGraphicsItem *> listItems = graphicsScene.items();
        for (int i = 0; i < listItems.size(); ++i)
            if (typeid(*(listItems[i])) == typeid(GraphicsFurnitureItem) &&
                    dynamic_cast<GraphicsFurnitureItem *>(listItems[i])->isContain(listExObj[ind]))
            {
                graphicsScene.removeItem(listItems[i]);
                break;
            }

        delete listExObj[ind];
        listExObj.removeAt(ind);

        emit vecExObjChanged();
    }
}

void SceneRedactorForm::on_lswdgExistingObjects_itemClicked(QListWidgetItem *item)
{
    if (ui->lswdgExistingObjects->currentItem() && !listExObj.isEmpty())
    {
        int ind = ui->lswdgExistingObjects->row(ui->lswdgExistingObjects->currentItem());

        QList<QGraphicsItem *> listItems = graphicsScene.items();
        for (int i = 0; i < listItems.size(); ++i)
            if (typeid(*(listItems[i])) == typeid(GraphicsFurnitureItem) &&
                    dynamic_cast<GraphicsFurnitureItem *>(listItems[i])->isContain(listExObj[ind]))
            {
                //graphicsScene.removeItem(listItems[i]);
                graphicsScene.clearSelection();
                listItems[i]->setSelected(true);

                break;
            }
    }
}

void SceneRedactorForm::on_btnOk_clicked()
{
    QList<FigureMetaData *> list;
    for (int i = 0; i < listExObj.size(); ++i)
    {
        list.push_back(new FigureMetaData());
        *list[i] = *listExObj[i];
    }
    emit sceneEditedSignal(SceneMetaData(graphicsScene.width(), graphicsScene.height(), listExObj));
    hide();
}
