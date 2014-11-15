#include "SceneMetaData.h"

SceneMetaData::SceneMetaData()
{
    sceneLengthOX = 0;
    sceneLengthOZ = 0;
}

SceneMetaData::SceneMetaData(qreal sceneLengthOX, qreal sceneLengthOZ, QList<FigureMetaData> list)
{
    this->sceneLengthOX = sceneLengthOX;
    this->sceneLengthOZ = sceneLengthOZ;
    listFig = list;
}

qreal SceneMetaData::getSceneLengthOX() const
{
    return sceneLengthOX;
}

void SceneMetaData::setSceneLengthOX(const qreal &value)
{
    sceneLengthOX = value;
}

qreal SceneMetaData::getSceneLengthOZ() const
{
    return sceneLengthOZ;
}

void SceneMetaData::setSceneLengthOZ(const qreal &value)
{
    sceneLengthOZ = value;
}


QList<FigureMetaData> SceneMetaData::getListFig() const
{
    return listFig;
}

void SceneMetaData::setListFig(const QList<FigureMetaData> &list)
{
    listFig = list;
}
