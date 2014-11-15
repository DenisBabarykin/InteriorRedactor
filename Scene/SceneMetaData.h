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

    qreal getSceneLengthOX() const;
    void setSceneLengthOX(const qreal &value);

    qreal getSceneLengthOZ() const;
    void setSceneLengthOZ(const qreal &value);

    QList<FigureMetaData> getListFig() const;
    void setListFig(const QList<FigureMetaData> &list);
};

#endif // SCENEMETADATA_H
