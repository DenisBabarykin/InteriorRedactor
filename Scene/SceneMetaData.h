#ifndef SCENEMETADATA_H
#define SCENEMETADATA_H

#include <QList>
#include "FigureMetaData.h"

class SceneMetaData
{
private:
    qreal sceneLengthOX;
    qreal sceneLengthOZ;

    QList<FigureMetaData *> listFig;

public:
    SceneMetaData();
    SceneMetaData(const SceneMetaData &scn);
    SceneMetaData(qreal sceneLengthOX, qreal sceneLengthOZ, QList<FigureMetaData *> list);
    ~SceneMetaData();

    qreal GetSceneLengthOX() const;
    void SetSceneLengthOX(const qreal &value);

    qreal GetSceneLengthOZ() const;
    void SetSceneLengthOZ(const qreal &value);

    QList<FigureMetaData *> getListFig();
    void setListFig(const QList<FigureMetaData *> &list);

    void SaveToFile(QString filename);
    void LoadFromFile(QString filename);

    SceneMetaData &operator=(SceneMetaData &scn);
};

#endif // SCENEMETADATA_H
