#include <stdio.h>
#include <string.h>
#include "obj_loader.h"

int load_obj(char *s, model_t *obj)
{
	FILE *fp = NULL; 
	
	vert_t vert[9999]; 
	uv_t   uv  [9999];
	face_t faces[9999];
	
	unsigned int vert_length = 0;
	unsigned int uv_length = 0;  
	unsigned int face_length = 0; 
	
	int result = 0; 
	
	if((fp = fopen(s, "r")) == NULL)
	{
		printf("failed to load file, idk why, good luck fixing it\n");
	}	
	
	while(!feof(fp))
	{
		char buffer [128]; 
		result = fscanf(fp, "%s", buffer);
		
		if (result == EOF)break; 
		
		if (strcmp(buffer, "v") == 0)
		{
			fscanf(fp, "%f %f %f\n", &vert[vert_length].x, 
								     &vert[vert_length].y, 
								     &vert[vert_length].z);
								     vert[vert_length].w = 1;
								   
			printf("Vert %f | %f | %f\n", vert[vert_length].x,
										  vert[vert_length].y,
				 						  vert[vert_length].z);								   	
								   
			vert_length++; 
		}
		
		if (strcmp(buffer, "f") == 0)
		{
			fscanf(fp, "%d %d %d\n", &faces[face_length].vx, 
								     &faces[face_length].vy, 
								     &faces[face_length].vz);
								   
			printf("face %d | %d | %d\n", faces[face_length].vx,
										  faces[face_length].vy,
				 						  faces[face_length].vz);								   
								   
			face_length++; 
		}
	}
	
	memcpy(obj->vert, vert, sizeof(vert_t)*vert_length);
	memcpy(obj->faces, faces, sizeof(face_t)*face_length);
	
	obj->vert_length = vert_length; 
	obj->face_length = face_length; 
	
	return 0; 
}
