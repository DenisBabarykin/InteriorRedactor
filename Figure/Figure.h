#ifndef FIGURE_H
#define FIGURE_H

#include "./ObjLoader/obj_parser.h"
#include "MeasuredFigure.h"
#include <QPainter>

class Figure : public MeasuredFigure
{
public:
    Figure();
    ~Figure();

    int load(const char *filename);

    void DrawModel(QPainter &painter); // Рисование каркаса
    void Rotate(const Figure *baseModel, qreal angleOX, qreal angleOY);// Вращение относительно базовой модели
    void Perspective(const Figure *baseModel);     // Перспективные преобразования относительно базовой модели
    void Shift(const Figure *baseModel, qreal dx, qreal dy, qreal dz); // Сдвиг относительно базовой модели

    virtual Point3D MaxPoint();
    virtual Point3D MinPoint();

    Figure *Clone();

    static Figure *CreateFloor(qreal lengthOX, qreal lengthOZ);

private:
    void Center();

public:

	obj_vector **vertexList;
	obj_vector **normalList;
	obj_vector **textureList;
	
	obj_face **faceList;
	obj_sphere **sphereList;
	obj_plane **planeList;
	
	obj_light_point **lightPointList;
	obj_light_quad **lightQuadList;
	obj_light_disc **lightDiscList;
	
	obj_material **materialList;
	
	int vertexCount;
	int normalCount;
	int textureCount;

	int faceCount;
	int sphereCount;
	int planeCount;

	int lightPointCount;
	int lightQuadCount;
	int lightDiscCount;

	int materialCount;

	obj_camera *camera;

private:
	obj_scene_data data;

};

#endif
