#include "Scene.h"
#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

const int CORES_COUNT = QThread::idealThreadCount();

void Scene::ShiftPartly(int downBorder, int upBorder, qreal dx, qreal dy, qreal dz)
{
    for (int i = downBorder; i <= upBorder; ++i)
        listFigWork[i]->Shift(listFigWork[i], dx, dy, dz);
}

void Scene::RotatePartly(int downBorder, int upBorder, qreal angleOX, qreal angleOY)
{
    for (int i = downBorder; i <= upBorder; ++i)
        listFigWork[i]->Rotate(listFigOrig[i], angleOX, angleOY);
}

void Scene::PerspectivePartly(int downBorder, int upBorder)
{
    for (int i = downBorder; i <= upBorder; ++i)
        listFigWork[i]->Perspective(listFigWork[i]);
}

Scene::Scene()
{
}

Scene::~Scene()
{
    Clear();
}

void Scene::ContainersFill()
{
    for (int i = 0, k = 0, a = 0, b = 0, c = 0; i < listFigOrig.size(); ++i)
    {
        for (int j = 0; j < listFigOrig[i]->faceCount; ++j)
        {
            for (int v = 0; v < 3; ++v)
                surfaces[c].vertexIndexes[v] = listFigOrig[i]->faceList[j]->vertex_index[v] + k;

            for (int v = 0; v < 3; ++v)
                surfaces[c].normalIndexes[v] = listFigOrig[i]->faceList[j]->normal_index[v] + a;

            surfaces[c].materialIndex = listFigOrig[i]->faceList[j]->material_index + b;
        }

        for (int j = 0; j < listFigOrig[i]->vertexCount; ++j)
            originalVertices[k++] = *(listFigOrig[i]->vertexList[j]);

        for (int j = 0; j < listFigOrig[i]->normalCount; ++j)
            originalNormals[a++] = *(listFigOrig[i]->normalList[j]);

        for (int j = 0; j < listFigOrig[i]->materialCount; ++j)
            materials[b++] = *(listFigOrig[i]->materialList[j]);
    }
}

void Scene::LoadScene(SceneMetaData *sceneMetaData)
{
    Clear();

    for (int i = 0; i < sceneMetaData->getListFig().size(); ++i)
    {
        Figure *objLoader = new Figure();
        qDebug() << "loading " << sceneMetaData->getListFig()[i]->GetFileName();
        objLoader->load(sceneMetaData->getListFig()[i]->GetFileName().toLocal8Bit().constData());
        qDebug() << "loading completed " << sceneMetaData->getListFig()[i]->GetFileName();

        objLoader->Shift(objLoader, sceneMetaData->getListFig()[i]->GetPos().rx() -
                        sceneMetaData->GetSceneLengthOX() / 2, 0,
                        sceneMetaData->getListFig()[i]->GetPos().ry() -
                        sceneMetaData->GetSceneLengthOZ() / 2);
        listFigOrig.push_back(objLoader);
    }

    // формирование пола и стен
    listFigOrig.push_back(Figure::CreateWalls(sceneMetaData->GetSceneLengthOX(), sceneMetaData->GetSceneLengthOZ(),
                                              250));
    listFigOrig.push_back(Figure::CreateFloor(sceneMetaData->GetSceneLengthOX(), sceneMetaData->GetSceneLengthOZ()));

    // Копирование оригинала в рабочую копию
    for (int i = 0; i < listFigOrig.size(); ++i)
        listFigWork.push_back((*listFigOrig[i]).Clone());

    //----------------
    int surfacesCount = 0;
    int verticesCount = 0;
    int normalsCount = 0;
    int materialsCount = 0;
    for (int i = 0; i < listFigOrig.size(); ++i)
    {
        surfacesCount += listFigOrig[i]->faceCount;
        verticesCount += listFigOrig[i]->vertexCount;
        normalsCount += listFigOrig[i]->normalCount;
        materialsCount += listFigOrig[i]->materialCount;
    }
    surfaces.resize(surfacesCount);
    originalVertices.resize(verticesCount);
    vertices.resize((verticesCount));
    originalNormals.resize(normalsCount);
    normals.resize((normalsCount));
    materials.resize(materialsCount);

    ContainersFill();

    emit SceneActionDoneSignal();
}

void Scene::Clear()
{
    if (!listFigOrig.empty())
    {
        for (int i = 0; i < listFigOrig.size(); ++i)
            delete listFigOrig[i];
        listFigOrig.clear();
    }
    if (!listFigWork.empty())
    {
        for (int i = 0; i < listFigWork.size(); ++i)
            delete listFigWork[i];
        listFigWork.clear();
    }
}

void Scene::Shift(qreal dx, qreal dy, qreal dz)
{
    if (CORES_COUNT < 3)
    {
        ShiftPartly(0, listFigOrig.size() - 1, dx, dy, dz);
    }
    else
    {
        int nExtraThreads = (CORES_COUNT - 1 < listFigOrig.size()) ?
                    (CORES_COUNT - 2) : (listFigOrig.size() - 1);
        QList<QFuture<void> > future;
        //QFuture<void> future[nExtraThreads];
        int nModelsForThread = listFigOrig.size() / (nExtraThreads + 1);

        for (int i = 0; i < nExtraThreads; ++i)
            future.append(QtConcurrent::run(this, &Scene::ShiftPartly,
                  i * nModelsForThread, (i + 1) * nModelsForThread - 1, dx, dy, dz));

        ShiftPartly(nExtraThreads * nModelsForThread, listFigOrig.size() - 1, dx, dy, dz);

        for (int i = 0; i < nExtraThreads; ++i)
            future[i].waitForFinished();
    }
}

void Scene::Rotate(qreal angleOX, qreal angleOY)
{
    if (CORES_COUNT < 3)
    {
        RotatePartly(0, listFigOrig.size() - 1, angleOX, angleOY);
    }
    else
    {
        int nExtraThreads = (CORES_COUNT - 1 < listFigOrig.size()) ?
                    (CORES_COUNT - 2) : (listFigOrig.size() - 1);
        //QFuture<void> future[nExtraThreads];
        QList<QFuture<void> > future;
        int nModelsForThread = listFigOrig.size() / (nExtraThreads + 1);

        for (int i = 0; i < nExtraThreads; ++i)
            future.append(QtConcurrent::run(this, &Scene::RotatePartly,
                  i * nModelsForThread, (i + 1) * nModelsForThread - 1, angleOX, angleOY));

        RotatePartly(nExtraThreads * nModelsForThread, listFigOrig.size() - 1, angleOX, angleOY);

        for (int i = 0; i < nExtraThreads; ++i)
            future[i].waitForFinished();
    }
}

void Scene::Perspective()
{
    if (CORES_COUNT < 3)
    {
        PerspectivePartly(0, listFigOrig.size() - 1);
    }
    else
    {
        int nExtraThreads = (CORES_COUNT - 1 < listFigOrig.size()) ?
                    (CORES_COUNT - 2) : (listFigOrig.size() - 1);
        //QFuture<void> future[nExtraThreads];
        QList<QFuture<void> > future;
        int nModelsForThread = listFigOrig.size() / (nExtraThreads + 1);

        for (int i = 0; i < nExtraThreads; ++i)
            future.append(QtConcurrent::run(this, &Scene::PerspectivePartly,
                  i * nModelsForThread, (i + 1) * nModelsForThread - 1));

        PerspectivePartly(nExtraThreads * nModelsForThread, listFigOrig.size() - 1);

        for (int i = 0; i < nExtraThreads; ++i)
            future[i].waitForFinished();
    }
}

bool Scene::IsEmpty()
{
    return listFigOrig.empty();
}
