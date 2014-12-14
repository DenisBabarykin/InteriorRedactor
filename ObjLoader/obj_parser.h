#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include "list.h"

#define OBJ_FILENAME_LENGTH 500
#define MATERIAL_NAME_SIZE 255
#define OBJ_LINE_SIZE 500
#define MAX_VERTEX_COUNT 4 // Треугольники или прямоугольники

class ObjFace
{
public:
	int vertex_index[MAX_VERTEX_COUNT];
	int normal_index[MAX_VERTEX_COUNT];
	int texture_index[MAX_VERTEX_COUNT];
	int vertex_count;
	int material_index;
};

class ObjSphere
{
public:
	int pos_index;
	int up_normal_index;
	int equator_normal_index;
	int texture_index[MAX_VERTEX_COUNT];
	int material_index;
};

class ObjPlane
{
public:
	int pos_index;
	int normal_index;
	int rotation_normal_index;
	int texture_index[MAX_VERTEX_COUNT];
	int material_index;
};

class ObjVector
{
public:
	double e[3];
};

class ObjMaterial
{
public:
	char name[MATERIAL_NAME_SIZE];
	char texture_filename[OBJ_FILENAME_LENGTH];
	double amb[3];
	double diff[3];
	double spec[3];
	double reflect;
	double refract;
	double trans;
	double shiny;
	double glossy;
	double refract_index;
};

class ObjCamera
{
public:
	int camera_pos_index;
	int camera_look_point_index;
	int camera_up_norm_index;
};

class ObjLightPoint
{
public:
	int pos_index;
	int material_index;
};

class ObjLightDisc
{
public:
	int pos_index;
	int normal_index;
	int material_index;
};

class ObjLightQuad
{
public:
	int vertex_index[MAX_VERTEX_COUNT];
	int material_index;
};

class ObjGrowableSceneData
{
public:
//	vector extreme_dimensions[2];
	char scene_filename[OBJ_FILENAME_LENGTH];
	char material_filename[OBJ_FILENAME_LENGTH];
	
	list vertex_list;
	list vertex_normal_list;
	list vertex_texture_list;
	
	list face_list;
	list sphere_list;
	list plane_list;
	
	list light_point_list;
	list light_quad_list;
	list light_disc_list;
	
	list material_list;
	
    ObjCamera *camera;
};

class ObjSceneData
{
public:
    ObjVector **vertex_list;
    ObjVector **vertex_normal_list;
    ObjVector **vertex_texture_list;
	
    ObjFace **face_list;
    ObjSphere **sphere_list;
    ObjPlane **plane_list;
	
    ObjLightPoint **light_point_list;
    ObjLightQuad **light_quad_list;
    ObjLightDisc **light_disc_list;
	
    ObjMaterial **material_list;
	
	int vertex_count;
	int vertex_normal_count;
	int vertex_texture_count;

	int face_count;
	int sphere_count;
	int plane_count;

	int light_point_count;
	int light_quad_count;
	int light_disc_count;

	int material_count;

    ObjCamera *camera;
};

int parse_obj_scene(ObjSceneData *data_out, const char *filename);
void delete_obj_data(ObjSceneData *data_out);

#endif
