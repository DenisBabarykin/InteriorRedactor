#include "Scene.h"
#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

const int CORES_COUNT = QThread::idealThreadCount();

void Scene::ShiftPartly(int downBorder, int upBorder, qreal dx, qreal dy, qreal dz)
{
    std::vector<ObjModel *>::iterator itBegin = listFigWork.begin();
    for (int i = 0; i < downBorder; ++i)
        ++itBegin;

    std::vector<ObjModel *>::iterator itOrigBegin = listFigOrig.begin();
    for (int i = 0; i < downBorder; ++i)
        ++itOrigBegin;

    std::vector<ObjModel *>::iterator itEnd = listFigWork.end();
    for (int i = 0; i < upBorder; ++i)
        ++itEnd;

    for ( ; itBegin <= itEnd; ++itBegin, ++itOrigBegin)
        (*itBegin)->Shift(*itOrigBegin, dx, dy, dz);
}

void Scene::RotatePartly(int downBorder, int upBorder, int angleOX, int angleOY)
{
    std::vector<ObjModel *>::iterator itBegin = listFigWork.begin();
    for (int i = 0; i < downBorder; ++i)
        ++itBegin;

    std::vector<ObjModel *>::iterator itOrigBegin = listFigOrig.begin();
    for (int i = 0; i < downBorder; ++i)
        ++itOrigBegin;

    std::vector<ObjModel *>::iterator itEnd = listFigWork.end();
    for (int i = 0; i < upBorder; ++i)
        ++itEnd;

    for ( ; itBegin <= itEnd; ++itBegin)
        (*itBegin)->Rotate(*itOrigBegin, angleOX, angleOY);
}

Scene::Scene()
{
}

Scene::~Scene()
{
    Clear();
}

void Scene::LoadScene(const SceneMetaData *sceneMetaData)
{
    Clear();

    for (int i = 0; i < sceneMetaData->getListFig().size(); ++i)
    {
        ObjLoader objLoader;
        qDebug() << "loading " << sceneMetaData.getListFig()[i].GetFileName();
        objLoader.load(sceneMetaData->getListFig()[i].GetFileName().toLocal8Bit().constData());
        qDebug() << "loading completed " << sceneMetaData->getListFig()[i].GetFileName();

        ObjModel *objModel = new ObjModel(objLoader);
        objModel->Shift(sceneMetaData.getListFig()[i].GetPos().rx(), 0, sceneMetaData.getListFig()[i].GetPos().ry());
        listFigOrig.push_back(objModel);
    }

    // формирование пола
    ObjModel *floor = new ObjModel;
    int dy = - 5; // чтобы исключить борьбу
    floor->vecPnts3D.append(Point3D(0, dy, 0));
    floor->vecPnts3D.append(Point3D(0, dy, sceneMetaData.GetSceneLengthOZ()));
    floor->vecPnts3D.append(Point3D(sceneMetaData.GetSceneLengthOX(), dy, sceneMetaData.GetSceneLengthOZ()));
    floor->vecPnts3D.append(Point3D(sceneMetaData.GetSceneLengthOX(), dy, 0));
    floor->vecIndx.append(FaceIndexes(0, 1, 2));
    floor->vecIndx.append(FaceIndexes(0, 2, 3));
    listFigOrig.push_front(floor);

    // Копирование оригинала в рабочую копию
    listFigWork.resize(listFigOrig.size());
    std::vector<ObjModel *>::iterator itOrig = listFigOrig.begin();
    std::vector<ObjModel *>::iterator itWork = listFigWork.begin();
    for ( ; itOrig < listFigOrig.end(); ++itOrig, ++itWork)
        *(*itWork) = *(*itOrig);

    Shift(vecModel, -sceneMetaData.GetSceneLengthOX() / 2, 0, - 3 * sceneMetaData.GetSceneLengthOZ() / 2);
    emit SceneActionDoneSignal();
}

void Scene::Clear()
{
    if (!listFigOrig.empty())
    {
        for (std::list<ObjModel *>::iterator it = listFigOrig.begin(); it != listFigOrig.end(); it++)
            delete *it;
        listFigOrig.clear();
    }
    if (!listFigWork.empty())
    {
        for (std::list<ObjModel *>::iterator it = listFigWork.begin(); it != listFigWork.end(); it++)
            delete *it;
        listFigWork.clear();
    }
}

void Scene::Shift(qreal dx, qreal dy, qreal dz)
{
    if (CORES_COUNT == -1 || CORES_COUNT == 1 || CORES_COUNT = 2)
    {
        ShiftPartly(0, listFigOrig.size() - 1, dx, dy, dz);
    }
    else
    {
        int nExtraThreads = (CORES_COUNT - 1 < listFigOrig.size()) ?
                    (CORES_COUNT - 2) : (listFigOrig.size() - 1);
        QFuture<void> future[nExtraThreads];
        int nModelsForThread = listFigOrig.size() / (nExtraThreads + 1);

        for (int i = 0; i < nExtraThreads; ++i)
            future[i] = QtConcurrent::run(this, &Scene::ShiftPartly,
                  i * nModelsForThread, (i + 1) * nModelsForThread - 1, dx, dy, dz);

        ShiftPartly(nExtraThreads * nModelsForThread, listFigOrig.size() - 1, dx, dy, dz);

        for (int i = 0; i < nExtraThreads; ++i)
            future[i].waitForFinished();
    }
    //emit SceneActionDoneSignal();
}

void Scene::Rotate(int angleOX, int angleOY)
{
    if (CORES_COUNT < 3)
    {
        RotatePartly(0, listFigOrig.size() - 1, angleOX, angleOY);
    }
    else
    {
        int nExtraThreads = (CORES_COUNT - 1 < listFigOrig.size()) ?
                    (CORES_COUNT - 2) : (listFigOrig.size() - 1);
        QFuture<void> future[nExtraThreads];
        int nModelsForThread = listFigOrig.size() / (nExtraThreads + 1);

        for (int i = 0; i < nExtraThreads; ++i)
            future[i] = QtConcurrent::run(this, &Scene::RotatePartly,
                  i * nModelsForThread, (i + 1) * nModelsForThread - 1, angleOX, angleOY);

        RotatePartly(nExtraThreads * nModelsForThread, listFig.size() - 1, angleOX, angleOY);

        for (int i = 0; i < nExtraThreads; ++i)
            future[i].waitForFinished();
    }
    //emit SceneActionDoneSignal();
}
