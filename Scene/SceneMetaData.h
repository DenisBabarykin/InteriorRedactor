#ifndef SCENEMETADATA_H
#define SCENEMETADATA_H

#include <QList>
#include "FigureMetaData.h"

class SceneMetaData
{
private:
    qreal sceneLengthOX;
    qreal sceneLengthOZ;

    QList<FigureMetaData> listFig;

public:
    SceneMetaData();
    SceneMetaData(qreal sceneLengthOX, qreal sceneLengthOZ, QList<FigureMetaData> list);

    qreal GetSceneLengthOX() const;
    void SetSceneLengthOX(const qreal &value);

    qreal GetSceneLengthOZ() const;
    void SetSceneLengthOZ(const qreal &value);

    QList<FigureMetaData> getListFig();
    void setListFig(const QList<FigureMetaData> &list);

    void SaveToFile(QString filename);
    void LoadFromFile(QString filename);

    SceneMetaData operator=(SceneMetaData &rs);
    SceneMetaData(const SceneMetaData &in);
};

#endif // SCENEMETADATA_H
