#include "SceneMetaData.h"
#include <QFile>
#include <QTextStream>
#include "./Exception/OpeningFileException.h"
#include <QDebug>

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

QList<FigureMetaData> SceneMetaData::getListFig()
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

    QTextStream tstream(&file);

    tstream << GetSceneLengthOX() << endl;
    tstream << GetSceneLengthOZ() << endl;

    tstream << listFig.size() << endl << endl;
    for (int i = 0; i < listFig.size(); ++i)
        tstream << listFig[i] << endl;

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

    QTextStream tstream(&file);
    bool doub = (sizeof(qreal) == sizeof(double)) ? (true) : (false);
    sceneLengthOX = (doub) ? (tstream.readLine().toDouble()) : (tstream.readLine().toFloat());
    sceneLengthOZ = (doub) ? (tstream.readLine().toDouble()) : (tstream.readLine().toFloat());

    int figCount = tstream.readLine().toInt();
    listFig.clear();

    for (int i = 0; i < figCount; ++i)
    {
        FigureMetaData tempFig;
        tstream.readLine();  // пропустить пустую строку
        tstream >> tempFig;
        listFig.append(tempFig);
    }

    file.close();
}
