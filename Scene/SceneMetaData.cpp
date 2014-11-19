#include "SceneMetaData.h"
#include <QFile>
#include <QTextStream>
#include "./Exception/OpeningFileException.h"

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

qreal SceneMetaData::GetSceneLengthOX() const
{
    return sceneLengthOX;
}

void SceneMetaData::SetSceneLengthOX(const qreal &value)
{
    sceneLengthOX = value;
}

qreal SceneMetaData::GetSceneLengthOZ() const
{
    return sceneLengthOZ;
}

void SceneMetaData::SetSceneLengthOZ(const qreal &value)
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

void SceneMetaData::SaveToFile(QString filename)
{
    QFile file(filename);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        OpeningFileException ex(filename);
        ex.raise();
    }

    QTextStream stream(&file);

    stream << GetSceneLengthOX() << endl;
    stream << GetSceneLengthOZ() << endl;

    stream << listFig.size() << endl << endl;
    for (int i = 0; i < listFig.size(); ++i)
        stream << listFig[i] << endl;

    file.flush(); //переносим данные из буфера в файл
    file.close();
}

void SceneMetaData::LoadFromFile(QString filename)
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        OpeningFileException ex(filename);
        ex.raise();
    }

    QTextStream stream(&file);

    stream >> sceneLengthOX;
    stream >> sceneLengthOZ;

    int figCount;
    stream >> figCount;
    listFig.clear();

    for (int i = 0; i < figCount; ++i)
    {
        FigureMetaData tempFig;
        stream >> tempFig;
        listFig.append(tempFig);
    }

    file.close();
}
