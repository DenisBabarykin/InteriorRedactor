#include "ObjModel.h"

ObjModel::ObjModel(ObjLoader &objLoader)
{
    fillDataFromObjLoader(objLoader);
}

void ObjModel::fillDataFromObjLoader(ObjLoader &objLoader)
{
    vecPnts3D.resize(objLoader.vertexCount);
    vecIndx.resize(objLoader.faceCount);

    for (int i = 0; i < vecPnts3D.count(); ++i)
        vecPnts3D[i] = Point3D(objLoader.vertexList[i]->e[0], objLoader.vertexList[i]->e[1],
                objLoader.vertexList[i]->e[2]);

    for (int i = 0; i < vecIndx.count(); ++i)
    {
        if (objLoader.faceList[i]->vertex_count != 3)
            throw ("Vertex count error");

        vecIndx[i] = FaceIndexes(objLoader.faceList[i]->vertex_index[0],
                objLoader.faceList[i]->vertex_index[1], objLoader.faceList[i]->vertex_index[2]);
    }
}
