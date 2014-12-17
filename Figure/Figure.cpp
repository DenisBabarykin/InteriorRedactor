#include "Figure.h"
#include "./ObjLoader/obj_parser.h"
#include <QtMath>

const qreal Pi = 3.14159265;
const qreal dy = -5;

int Figure::load(const char *filename)
{
	int no_error = 1;
	no_error = parse_obj_scene(&data, filename);
	if(no_error)
	{
		this->vertexCount = data.vertex_count;
		this->normalCount = data.vertex_normal_count;
		this->textureCount = data.vertex_texture_count;

		this->faceCount = data.face_count;
		this->sphereCount = data.sphere_count;
		this->planeCount = data.plane_count;

		this->lightPointCount = data.light_point_count;
		this->lightDiscCount = data.light_disc_count;
		this->lightQuadCount = data.light_quad_count;

		this->materialCount = data.material_count;

		this->vertexList = data.vertex_list;
		this->normalList = data.vertex_normal_list;
		this->textureList = data.vertex_texture_list;

		this->faceList = data.face_list;
		this->sphereList = data.sphere_list;
		this->planeList = data.plane_list;

		this->lightPointList = data.light_point_list;
		this->lightDiscList = data.light_disc_list;
		this->lightQuadList = data.light_quad_list;

		this->materialList = data.material_list;

		this->camera = data.camera;

        Center();
	}

    return no_error;
}

void Figure::DrawModel(QPainter &painter)
{
    for (int i = 0; i < faceCount; ++i)
    {
        // От 0-ой к 1-ой вершине i-ой поверхности
        painter.drawLine(vertexList[ faceList[i]->vertex_index[0] ]->e[0],
                vertexList[ faceList[i]->vertex_index[0] ]->e[1],
                vertexList[ faceList[i]->vertex_index[1] ]->e[0],
                vertexList[ faceList[i]->vertex_index[1] ]->e[1]);

        // От 1-ой ко 2-ой вершине i-ой поверхности
        painter.drawLine(vertexList[ faceList[i]->vertex_index[1] ]->e[0],
                vertexList[ faceList[i]->vertex_index[1] ]->e[1],
                vertexList[ faceList[i]->vertex_index[2] ]->e[0],
                vertexList[ faceList[i]->vertex_index[2] ]->e[1]);

        // От 0-ой ко 2-ой вершине i-ой поверхности
        painter.drawLine(vertexList[ faceList[i]->vertex_index[0] ]->e[0],
                vertexList[ faceList[i]->vertex_index[0] ]->e[1],
                vertexList[ faceList[i]->vertex_index[2] ]->e[0],
                vertexList[ faceList[i]->vertex_index[2] ]->e[1]);
    }
}

void Figure::Rotate(const Figure *baseModel, qreal angleOX, qreal angleOY)
{
    angleOX *= Pi / 180;
    angleOY *= Pi / 180;
    for (int i = 0; i < vertexCount; ++i)
    {
        vertexList[i]->e[0] = baseModel->vertexList[i]->e[0] * cos(angleOY) +
                baseModel->vertexList[i]->e[2] * sin(angleOY);
        qreal newZ = - baseModel->vertexList[i]->e[0] * sin(angleOY) +
                baseModel->vertexList[i]->e[2] * cos(angleOY);

        vertexList[i]->e[1] = baseModel->vertexList[i]->e[1] * cos(angleOX) - newZ * sin(angleOX);
        vertexList[i]->e[2] = baseModel->vertexList[i]->e[1] * sin(angleOX) + newZ * cos(angleOX);
    }
    for (int i = 0; i < normalCount; ++i)
    {
        normalList[i]->e[0] = baseModel->normalList[i]->e[0] * cos(angleOY) +
                baseModel->normalList[i]->e[2] * sin(angleOY);
        qreal newZ = - baseModel->normalList[i]->e[0] * sin(angleOY) +
                baseModel->normalList[i]->e[2] * cos(angleOY);

        normalList[i]->e[1] = baseModel->normalList[i]->e[1] * cos(angleOX) - newZ * sin(angleOX);
        normalList[i]->e[2] = baseModel->normalList[i]->e[1] * sin(angleOX) + newZ * cos(angleOX);
    }
}

void Figure::Perspective(const Figure *baseModel)
{
    qreal fov = 700; // field of view - поле зрения
    qreal absZ;
    for (int i = 0; i < vertexCount; ++i)
    {
        absZ = fabs(vertexList[i]->e[2]);
        //absZ = vertexList[i]->e[2];
        vertexList[i]->e[0] =  baseModel->vertexList[i]->e[0] / absZ * fov;
        vertexList[i]->e[1] =  baseModel->vertexList[i]->e[1] / absZ * fov;
    }
    /*
    for (int i = 0; i < normalCount; ++i)
    {
        absZ = fabs(normalList[i]->e[2]);
        //absZ = vertexList[i]->e[2];
        normalList[i]->e[0] =  baseModel->normalList[i]->e[0] / absZ * fov;
        normalList[i]->e[1] =  baseModel->normalList[i]->e[1] / absZ * fov;
    }
    */
}

void Figure::Shift(const Figure *baseModel, qreal dx, qreal dy, qreal dz)
{
    for (int i = 0; i < vertexCount; ++i)
    {
        vertexList[i]->e[0] = baseModel->vertexList[i]->e[0] + dx;
        vertexList[i]->e[1] = baseModel->vertexList[i]->e[1] + dy;
        vertexList[i]->e[2] = baseModel->vertexList[i]->e[2] + dz;
    }
}

Point3D Figure::MaxPoint()
{
    Point3D maxPoint(vertexList[0]->e[0], vertexList[0]->e[1], vertexList[0]->e[2]);

    for (int i = 0; i < vertexCount; ++i)
    {
        if (vertexList[i]->e[0] > maxPoint.x)
            maxPoint.x = vertexList[i]->e[0];

        if (vertexList[i]->e[1] > maxPoint.y)
            maxPoint.y = vertexList[i]->e[1];

        if (vertexList[i]->e[2] > maxPoint.z)
            maxPoint.z = vertexList[i]->e[2];
    }

    return maxPoint;
}

Point3D Figure::MinPoint()
{
    Point3D minPoint(vertexList[0]->e[0], vertexList[0]->e[1], vertexList[0]->e[2]);

    for (int i = 0; i < vertexCount; ++i)
    {
        if (vertexList[i]->e[0] < minPoint.x)
            minPoint.x = vertexList[i]->e[0];

        if (vertexList[i]->e[1] < minPoint.y)
            minPoint.y = vertexList[i]->e[1];

        if (vertexList[i]->e[2] < minPoint.z)
            minPoint.z = vertexList[i]->e[2];
    }

    return minPoint;
}

Figure *Figure::Clone()
{
    Figure *fig = new Figure();

    fig->vertexCount = vertexCount;
    if (vertexCount > 0)
    {
        fig->vertexList = (ObjVector **) malloc(vertexCount * sizeof(ObjVector *));
        for (int i = 0; i < vertexCount; ++i)
        {
            fig->vertexList[i] = (ObjVector *) malloc(sizeof(ObjVector));
            *(fig->vertexList[i]) = *(vertexList[i]);
        }
    }
    fig->data.vertex_list = fig->vertexList;
    fig->data.vertex_count = fig->vertexCount;

    fig->normalCount = normalCount;
    if (normalCount > 0)
    {
        fig->normalList = (ObjVector **) malloc(normalCount * sizeof(ObjVector *));
        for (int i = 0; i < normalCount; ++i)
        {
            fig->normalList[i] = (ObjVector *) malloc(sizeof(ObjVector));
            *(fig->normalList[i]) = *(normalList[i]);
        }
    }
    fig->data.vertex_normal_count = fig->normalCount;
    fig->data.vertex_normal_list = fig->normalList;

    fig->textureCount = textureCount;
    if (textureCount > 0)
    {
        fig->textureList = (ObjVector **) malloc(textureCount * sizeof(ObjVector *));
        for (int i = 0; i < textureCount; ++i)
        {
            fig->textureList[i] = (ObjVector *) malloc(sizeof(ObjVector));
            *(fig->textureList[i]) = *(textureList[i]);
        }
    }
    fig->data.vertex_texture_count = fig->textureCount;
    fig->data.vertex_texture_list = fig->textureList;

    fig->faceCount = faceCount;
    if (faceCount > 0)
    {
        fig->faceList = (ObjFace **) malloc(faceCount * sizeof(ObjFace *));
        for (int i = 0; i < faceCount; ++i)
        {
            fig->faceList[i] = (ObjFace *) malloc(sizeof(ObjFace));
            *(fig->faceList[i]) = *(faceList[i]);
        }
    }
    fig->data.face_count = fig->faceCount;
    fig->data.face_list = fig->faceList;

    fig->sphereCount = sphereCount;
    if (sphereCount > 0)
    {
        fig->sphereList = (ObjSphere **) malloc(sphereCount * sizeof(ObjSphere *));
        for (int i = 0; i < sphereCount; ++i)
        {
            fig->sphereList[i] = (ObjSphere *) malloc(sizeof(ObjSphere));
            *(fig->sphereList[i]) = *(sphereList[i]);
        }
    }
    fig->data.sphere_count = fig->sphereCount;
    fig->data.sphere_list = fig->sphereList;

    fig->planeCount = planeCount;
    if (planeCount > 0)
    {
        fig->planeList = (ObjPlane **) malloc(planeCount * sizeof(ObjPlane *));
        for (int i = 0; i < planeCount; ++i)
        {
            fig->planeList[i] = (ObjPlane *) malloc(sizeof(ObjPlane));
            *(fig->planeList[i]) = *(planeList[i]);
        }
    }
    fig->data.plane_count = fig->planeCount;
    fig->data.plane_list = fig->planeList;

    fig->lightPointCount = lightPointCount;
    if (lightPointCount > 0)
    {
        fig->lightPointList = (ObjLightPoint **) malloc(lightPointCount * sizeof(ObjLightPoint *));
        for (int i = 0; i < lightPointCount; ++i)
        {
            fig->lightPointList[i] = (ObjLightPoint *) malloc(sizeof(ObjLightPoint));
            *(fig->lightPointList[i]) = *(lightPointList[i]);
        }
    }
    fig->data.light_point_count = fig->lightPointCount;
    fig->data.light_point_list = fig->lightPointList;

    fig->lightQuadCount = lightQuadCount;
    if (lightQuadCount > 0)
    {
        fig->lightQuadList = (ObjLightQuad **) malloc(lightQuadCount * sizeof(ObjLightQuad *));
        for (int i = 0; i < lightQuadCount; ++i)
        {
            fig->lightQuadList[i] = (ObjLightQuad *) malloc(sizeof(ObjLightQuad));
            *(fig->lightQuadList[i]) = *(lightQuadList[i]);
        }
    }
    fig->data.light_quad_count = fig->lightQuadCount;
    fig->data.light_quad_list = fig->lightQuadList;

    fig->lightDiscCount = lightDiscCount;
    if (lightDiscCount > 0)
    {
        fig->lightDiscList = (ObjLightDisc **) malloc(lightDiscCount * sizeof(ObjLightDisc *));
        for (int i = 0; i < lightDiscCount; ++i)
        {
            fig->lightDiscList[i] = (ObjLightDisc *) malloc(sizeof(ObjLightDisc));
            *(fig->lightDiscList[i]) = *(lightDiscList[i]);
        }
    }
    fig->data.light_disc_count = fig->lightDiscCount;
    fig->data.light_disc_list = fig->lightDiscList;

    fig->materialCount = materialCount;
    if (materialCount > 0)
    {
        fig->materialList = (ObjMaterial **) malloc(materialCount * sizeof(ObjMaterial *));
        for (int i = 0; i < materialCount; ++i)
        {
            fig->materialList[i] = (ObjMaterial *) malloc(sizeof(ObjMaterial));
            *(fig->materialList[i]) = *(materialList[i]);
        }
    }
    fig->data.material_count = fig->materialCount;
    fig->data.material_list = fig->materialList;

    if (camera)
    {
        fig->camera = (ObjCamera *) malloc(sizeof(ObjCamera));
        *(fig->camera) = *camera;
    }
    fig->data.camera = fig->camera;

    return fig;
}

Figure *Figure::CreateFloor(qreal lengthOX, qreal lengthOZ)
{
    Figure *fig = new Figure();

    // Выделение памяти под вершины
    fig->vertexCount = 4;
    fig->vertexList = (ObjVector **) malloc(fig->vertexCount * sizeof(ObjVector *));
    for (int i = 0; i < fig->vertexCount; ++i)
        fig->vertexList[i] = (ObjVector *) malloc(sizeof(ObjVector));
    fig->data.vertex_list = fig->vertexList;
    fig->data.vertex_count = fig->vertexCount;

    // Выделение памяти под нормаль
    fig->normalCount = 1;
    fig->normalList = (ObjVector **) malloc(fig->normalCount * sizeof(ObjVector *));
    fig->normalList[0] = (ObjVector *) malloc(sizeof(ObjVector));
    fig->data.vertex_normal_count = fig->normalCount;
    fig->data.vertex_normal_list = fig->normalList;

    // Выделение памяти под поверхности
    fig->faceCount = 2;
    fig->faceList = (ObjFace **) malloc(fig->faceCount * sizeof(ObjFace *));
    for (int i = 0; i < fig->faceCount; ++i)
        fig->faceList[i] = (ObjFace *) malloc(sizeof(ObjFace));
    fig->data.face_count = fig->faceCount;
    fig->data.face_list = fig->faceList;

    // Выделение памяти под материал
    fig->materialCount = 1;
    fig->materialList = (ObjMaterial **) malloc(fig->materialCount * sizeof(ObjMaterial *));
    fig->materialList[0] = (ObjMaterial *) malloc(sizeof(ObjMaterial));
    fig->data.material_count = fig->materialCount;
    fig->data.material_list = fig->materialList;


    // Заполнение вершин
    fig->vertexList[0]->e[0] = - lengthOX / 2; // 1ая точка
    fig->vertexList[0]->e[1] = dy;
    fig->vertexList[0]->e[2] = - lengthOZ / 2;

    fig->vertexList[1]->e[0] = - lengthOX / 2; // 2ая точка
    fig->vertexList[1]->e[1] = dy;
    fig->vertexList[1]->e[2] = lengthOZ / 2;

    fig->vertexList[2]->e[0] = lengthOX / 2; // 3ья точка
    fig->vertexList[2]->e[1] = dy;
    fig->vertexList[2]->e[2] = lengthOZ / 2;

    fig->vertexList[3]->e[0] = lengthOX / 2; // 4ая точка
    fig->vertexList[3]->e[1] = dy;
    fig->vertexList[3]->e[2] = - lengthOZ / 2;

    // Заполнение нормали
    fig->normalList[0]->e[0] = 0; // Эта нормаль одинакова для всех вершин пола
    fig->normalList[0]->e[1] = 1;
    fig->normalList[0]->e[2] = 0;

    // Заполнение поверхностей
    fig->faceList[0]->vertex_index[0] = 0; // Вершины
    fig->faceList[0]->vertex_index[1] = 1;
    fig->faceList[0]->vertex_index[2] = 2;

    fig->faceList[1]->vertex_index[0] = 0;
    fig->faceList[1]->vertex_index[1] = 2;
    fig->faceList[1]->vertex_index[2] = 3;

    fig->faceList[0]->normal_index[0] = 0; // Нормали
    fig->faceList[0]->normal_index[1] = 0;
    fig->faceList[0]->normal_index[2] = 0;

    fig->faceList[1]->normal_index[0] = 0;
    fig->faceList[1]->normal_index[1] = 0;
    fig->faceList[1]->normal_index[2] = 0;

    fig->faceList[0]->material_index = 0; // Индекс материала
    fig->faceList[1]->material_index = 0;

    // Заполнение материала
    fig->materialList[0]->diff[0] = 0.513; // Цвет диффузного отражения
    fig->materialList[0]->diff[1] = 0.545;
    fig->materialList[0]->diff[2] = 0.545;

    return fig;
}

Figure *Figure::CreateWalls(qreal lengthOX, qreal lengthOZ, qreal height)
{
    Figure *fig = new Figure();

    // Выделение памяти под вершины
    fig->vertexCount = 8;
    fig->vertexList = (ObjVector **) malloc(fig->vertexCount * sizeof(ObjVector *));
    for (int i = 0; i < fig->vertexCount; ++i)
        fig->vertexList[i] = (ObjVector *) malloc(sizeof(ObjVector));
    fig->data.vertex_list = fig->vertexList;
    fig->data.vertex_count = fig->vertexCount;

    // Выделение памяти под нормали
    fig->normalCount = 4;
    fig->normalList = (ObjVector **) malloc(fig->normalCount * sizeof(ObjVector *));
    for (int i = 0; i < fig->normalCount; ++i)
        fig->normalList[i] = (ObjVector *) malloc(sizeof(ObjVector));
    fig->data.vertex_normal_count = fig->normalCount;
    fig->data.vertex_normal_list = fig->normalList;

    // Выделение памяти под поверхности
    fig->faceCount = 8;
    fig->faceList = (ObjFace **) malloc(fig->faceCount * sizeof(ObjFace *));
    for (int i = 0; i < fig->faceCount; ++i)
        fig->faceList[i] = (ObjFace *) malloc(sizeof(ObjFace));
    fig->data.face_count = fig->faceCount;
    fig->data.face_list = fig->faceList;

    // Выделение памяти под материал
    fig->materialCount = 1;
    fig->materialList = (ObjMaterial **) malloc(fig->materialCount * sizeof(ObjMaterial *));
    fig->materialList[0] = (ObjMaterial *) malloc(sizeof(ObjMaterial));
    fig->data.material_count = fig->materialCount;
    fig->data.material_list = fig->materialList;


    // Заполнение вершин
    fig->vertexList[0]->e[0] = - lengthOX / 2; // низ
    fig->vertexList[0]->e[1] = dy;
    fig->vertexList[0]->e[2] = - lengthOZ / 2;

    fig->vertexList[1]->e[0] = - lengthOX / 2;
    fig->vertexList[1]->e[1] = dy;
    fig->vertexList[1]->e[2] = lengthOZ / 2;

    fig->vertexList[2]->e[0] = lengthOX / 2;
    fig->vertexList[2]->e[1] = dy;
    fig->vertexList[2]->e[2] = lengthOZ / 2;

    fig->vertexList[3]->e[0] = lengthOX / 2;
    fig->vertexList[3]->e[1] = dy;
    fig->vertexList[3]->e[2] = - lengthOZ / 2;

    fig->vertexList[4]->e[0] = - lengthOX / 2; // верх
    fig->vertexList[4]->e[1] = dy + height;
    fig->vertexList[4]->e[2] = - lengthOZ / 2;

    fig->vertexList[5]->e[0] = - lengthOX / 2;
    fig->vertexList[5]->e[1] = dy + height;
    fig->vertexList[5]->e[2] = lengthOZ / 2;

    fig->vertexList[6]->e[0] = lengthOX / 2;
    fig->vertexList[6]->e[1] = dy + height;
    fig->vertexList[6]->e[2] = lengthOZ / 2;

    fig->vertexList[7]->e[0] = lengthOX / 2;
    fig->vertexList[7]->e[1] = dy + height;
    fig->vertexList[7]->e[2] = - lengthOZ / 2;

    // Заполнение нормалей
    fig->normalList[0]->e[0] = 1;
    fig->normalList[0]->e[1] = 0;
    fig->normalList[0]->e[2] = 0;

    fig->normalList[1]->e[0] = 0;
    fig->normalList[1]->e[1] = 0;
    fig->normalList[1]->e[2] = 1;

    fig->normalList[2]->e[0] = -1;
    fig->normalList[2]->e[1] = 0;
    fig->normalList[2]->e[2] = 0;

    fig->normalList[3]->e[0] = 0;
    fig->normalList[3]->e[1] = 0;
    fig->normalList[3]->e[2] = -1;

    // Заполнение поверхностей
    fig->faceList[0]->vertex_index[0] = 0; // Вершины
    fig->faceList[0]->vertex_index[1] = 1;
    fig->faceList[0]->vertex_index[2] = 5;

    fig->faceList[1]->vertex_index[0] = 0;
    fig->faceList[1]->vertex_index[1] = 4;
    fig->faceList[1]->vertex_index[2] = 5;

    fig->faceList[0]->normal_index[0] = 0; // Нормали
    fig->faceList[0]->normal_index[1] = 0;
    fig->faceList[0]->normal_index[2] = 0;

    fig->faceList[1]->normal_index[0] = 0;
    fig->faceList[1]->normal_index[1] = 0;
    fig->faceList[1]->normal_index[2] = 0;

    fig->faceList[2]->vertex_index[0] = 0; // Вершины
    fig->faceList[2]->vertex_index[1] = 3;
    fig->faceList[2]->vertex_index[2] = 7;

    fig->faceList[3]->vertex_index[0] = 0;
    fig->faceList[3]->vertex_index[1] = 4;
    fig->faceList[3]->vertex_index[2] = 7;

    fig->faceList[2]->normal_index[0] = 1; // Нормали
    fig->faceList[2]->normal_index[1] = 1;
    fig->faceList[2]->normal_index[2] = 1;

    fig->faceList[3]->normal_index[0] = 1;
    fig->faceList[3]->normal_index[1] = 1;
    fig->faceList[3]->normal_index[2] = 1;

    fig->faceList[4]->vertex_index[0] = 3; // Вершины
    fig->faceList[4]->vertex_index[1] = 2;
    fig->faceList[4]->vertex_index[2] = 6;

    fig->faceList[5]->vertex_index[0] = 3;
    fig->faceList[5]->vertex_index[1] = 7;
    fig->faceList[5]->vertex_index[2] = 6;

    fig->faceList[4]->normal_index[0] = 2; // Нормали
    fig->faceList[4]->normal_index[1] = 2;
    fig->faceList[4]->normal_index[2] = 2;

    fig->faceList[5]->normal_index[0] = 2;
    fig->faceList[5]->normal_index[1] = 2;
    fig->faceList[5]->normal_index[2] = 2;

    fig->faceList[6]->vertex_index[0] = 2; // Вершины
    fig->faceList[6]->vertex_index[1] = 1;
    fig->faceList[6]->vertex_index[2] = 6;

    fig->faceList[7]->vertex_index[0] = 1;
    fig->faceList[7]->vertex_index[1] = 5;
    fig->faceList[7]->vertex_index[2] = 6;

    fig->faceList[6]->normal_index[0] = 3; // Нормали
    fig->faceList[6]->normal_index[1] = 3;
    fig->faceList[6]->normal_index[2] = 3;

    fig->faceList[7]->normal_index[0] = 3;
    fig->faceList[7]->normal_index[1] = 3;
    fig->faceList[7]->normal_index[2] = 3;


    fig->faceList[0]->material_index = 0; // Индекс материала
    fig->faceList[1]->material_index = 0;
    fig->faceList[2]->material_index = 0;
    fig->faceList[3]->material_index = 0;
    fig->faceList[4]->material_index = 0;
    fig->faceList[5]->material_index = 0;
    fig->faceList[6]->material_index = 0;
    fig->faceList[7]->material_index = 0;

    // Заполнение материала
    fig->materialList[0]->diff[0] = 0.804; // Цвет диффузного отражения
    fig->materialList[0]->diff[1] = 0.717;
    fig->materialList[0]->diff[2] = 0.709;

    return fig;
}

void Figure::Center()
{
    Point3D maxPoint = MaxPoint();
    Point3D minPoint = MinPoint();

    qreal dx = - (maxPoint.x + minPoint.x) / 2;
    qreal dy = - minPoint.y;
    qreal dz = - (maxPoint.z + minPoint.z) / 2;

    for (int i = 0; i < vertexCount; ++i)
    {
        vertexList[i]->e[0] += dx;
        vertexList[i]->e[1] += dy;
        vertexList[i]->e[2] += dz;
    }
}

Figure::~Figure()
{
    delete_obj_data(&data);
}

Figure::Figure()
{
    data.vertex_list = vertexList = NULL;
    data.vertex_normal_list = normalList = NULL;
    data.vertex_texture_list = textureList = NULL;
    data.face_list = faceList = NULL;
    data.sphere_list = sphereList = NULL;
    data.plane_list = planeList = NULL;
    data.light_point_list = lightPointList = NULL;
    data.light_quad_list = lightQuadList = NULL;
    data.light_disc_list = lightDiscList = NULL;
    data.material_list = materialList = NULL;
    data.camera = camera = NULL;

    data.vertex_count = vertexCount = 0;
    data.vertex_normal_count = normalCount = 0;
    data.vertex_texture_count = textureCount = 0;
    data.face_count = faceCount = 0;
    data.sphere_count = sphereCount = 0;
    data.plane_count = planeCount = 0;
    data.light_point_count = lightPointCount = 0;
    data.light_quad_count = lightQuadCount = 0;
    data.light_disc_count = lightDiscCount = 0;
    data.material_count = materialCount = 0;
}
