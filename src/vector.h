#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef union
{	
	float index[4];
	struct
	{
		float x; 
		float y;
		float z; 
		float w; 
	};
}vec4_t

void vec4_position(vec4_t *v, float x, float y, float z);

#endif //__VECTOR_H__
