#ifndef __OBJ_LOADER_H__
#define __OBJ_LOADER_H__

#include <GL/gl.h>

typedef struct 
{
	float x, y, z, w;
}vert_t;

typedef struct
{
	float u, v;
}uv_t; 

typedef struct 
{
	unsigned int vx, vy, vz;
	unsigned int tx, ty, tz;
	//unsigned int vx, vy, vz;
}face_t;

typedef struct
{
	vert_t vert[9999];
	vert_t norm;  
	uv_t   uv;
	face_t faces[9999];
	
	unsigned int vert_length; 
	unsigned int uv_length;  
	unsigned int face_length; 
}model_t; 

int load_obj(char *s, model_t *obj);

#endif //__OBJ_LOADER_H__
