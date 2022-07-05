#include <math.h>
#include "matrix.h"

void matrix_identity(matrix4_t *m)
{
	m->e[0][0]=1; m->e[0][1]=0; m->e[0][2]=0; m->e[0][3]=0;
	m->e[1][0]=0; m->e[1][1]=1; m->e[1][2]=0; m->e[1][3]=0;
	m->e[2][0]=0; m->e[2][1]=0; m->e[2][2]=1; m->e[2][3]=0;
	m->e[3][0]=0; m->e[3][1]=0; m->e[3][2]=0; m->e[3][3]=1;
}

void matrix_vert_mul(matrix4_t *m, vert_t *des, vert_t *src)
{	
	des->x = m->e[0][0] * src->x + m->e[1][0] * src->y + m->e[2][0] * src->z + m->e[3][0] * src->w;
	des->y = m->e[0][1] * src->x + m->e[1][1] * src->y + m->e[2][1] * src->z + m->e[3][1] * src->w;
	des->z = m->e[0][2] * src->x + m->e[1][2] * src->y + m->e[2][2] * src->z + m->e[3][2] * src->w;
	float w = m->e[0][3] * src->x + m->e[1][3] * src->y + m->e[2][3] * src->z + m->e[3][3] * src->w;
	
	/*used for color shading (remove later)*/
	des->w = m->e[0][2] * src->x + m->e[1][2] * src->y + m->e[2][2] * src->z + m->e[3][2] * src->w;

	if (des->w != 1)
	{
		des->x /= w; 
		des->y /= w; 
		des->z /= w; 
	}
}

void matrix_matrix_mul(matrix4_t *m1, matrix4_t *m2)
{
	matrix4_t t; 
	
	t.e[0][0] = m1->e[0][0] * m2->e[0][0] + m1->e[0][1] * m2->e[1][0] + m1->e[0][2] * m2->e[2][0] + m1->e[0][3] * m2->e[3][0];
	t.e[0][1] = m1->e[0][0] * m2->e[0][1] + m1->e[0][1] * m2->e[1][1] + m1->e[0][2] * m2->e[2][1] + m1->e[0][3] * m2->e[3][1];
	t.e[0][2] = m1->e[0][0] * m2->e[0][2] + m1->e[0][1] * m2->e[1][2] + m1->e[0][2] * m2->e[2][2] + m1->e[0][3] * m2->e[3][2];
	t.e[0][3] = m1->e[0][0] * m2->e[0][3] + m1->e[0][1] * m2->e[1][3] + m1->e[0][2] * m2->e[2][3] + m1->e[0][3] * m2->e[3][3];
	
	t.e[1][0] = m1->e[1][0] * m2->e[0][0] + m1->e[1][1] * m2->e[1][0] + m1->e[1][2] * m2->e[2][0] + m1->e[1][3] * m2->e[3][0];
	t.e[1][1] = m1->e[1][0] * m2->e[0][1] + m1->e[1][1] * m2->e[1][1] + m1->e[1][2] * m2->e[2][1] + m1->e[1][3] * m2->e[3][1];
	t.e[1][2] = m1->e[1][0] * m2->e[0][2] + m1->e[1][1] * m2->e[1][2] + m1->e[1][2] * m2->e[2][2] + m1->e[1][3] * m2->e[3][2];
	t.e[1][3] = m1->e[1][0] * m2->e[0][3] + m1->e[1][1] * m2->e[1][3] + m1->e[1][2] * m2->e[2][3] + m1->e[1][3] * m2->e[3][3];	
	
	t.e[2][0] = m1->e[2][0] * m2->e[0][0] + m1->e[2][1] * m2->e[1][0] + m1->e[2][2] * m2->e[2][0] + m1->e[2][3] * m2->e[3][0];
	t.e[2][1] = m1->e[2][0] * m2->e[0][1] + m1->e[2][1] * m2->e[1][1] + m1->e[2][2] * m2->e[2][1] + m1->e[2][3] * m2->e[3][1];
	t.e[2][2] = m1->e[2][0] * m2->e[0][2] + m1->e[2][1] * m2->e[1][2] + m1->e[2][2] * m2->e[2][2] + m1->e[2][3] * m2->e[3][2];
	t.e[2][3] = m1->e[2][0] * m2->e[0][3] + m1->e[2][1] * m2->e[1][3] + m1->e[2][2] * m2->e[2][3] + m1->e[2][3] * m2->e[3][3];
	
	t.e[3][0] = m1->e[3][0] * m2->e[0][0] + m1->e[3][1] * m2->e[1][0] + m1->e[3][2] * m2->e[2][0] + m1->e[3][3] * m2->e[3][0];
	t.e[3][1] = m1->e[3][0] * m2->e[0][1] + m1->e[3][1] * m2->e[1][1] + m1->e[3][2] * m2->e[2][1] + m1->e[3][3] * m2->e[3][1];
	t.e[3][2] = m1->e[3][0] * m2->e[0][2] + m1->e[3][1] * m2->e[1][2] + m1->e[3][2] * m2->e[2][2] + m1->e[3][3] * m2->e[3][2];
	t.e[3][3] = m1->e[3][0] * m2->e[0][3] + m1->e[3][1] * m2->e[1][3] + m1->e[3][2] * m2->e[2][3] + m1->e[3][3] * m2->e[3][3];
	
	*m1 = t; 
}

void matrix_translate(matrix4_t *m, float x, float y, float z)
{
	matrix_identity(m);
	
	m->e[3][0]=x;
	m->e[3][1]=y;
	m->e[3][2]=z;
}

void matrix_same_scale(matrix4_t *m, float s)
{
	matrix_scale(m, s, s, s);
}

void matrix_scale(matrix4_t *m, float x, float y, float z)
{
	matrix_identity(m);
	
	m->e[0][0] = x;
	m->e[1][1] = y; 
	m->e[2][2] = z; 
}

void matrix_rot_x(matrix4_t *m, float rad)
{
	matrix_identity(m);
	
	m->e[1][1] = cosf(rad);
	m->e[1][2] =-sinf(rad); 
	m->e[2][1] = sinf(rad); 
	m->e[2][2] = cosf(rad); 
}

void matrix_rot_y(matrix4_t *m, float rad)
{
	matrix_identity(m); 
	
	m->e[0][0] = cosf(rad);
	m->e[0][2] = sinf(rad); 
	m->e[2][0] =-sinf(rad); 
	m->e[2][2] = cosf(rad); 
}

void matrix_rot_z(matrix4_t *m, float rad)
{
	matrix_identity(m); 
	
	m->e[0][0] = cosf(rad);
	m->e[0][1] =-sinf(rad); 
	m->e[1][0] = sinf(rad); 
	m->e[1][1] = cosf(rad); 
}

void matrix_projection(matrix4_t *m, float fov, float aspect, float near, float far)
{
 	float fov_half = fov * 0.5f; 
	float cot = 1.0f/tanf(DEGTORAD(fov_half)); 
	float fmn = far - near; 

	matrix_identity(m);
	
	m->e[0][0] = cot / aspect;
	m->e[1][1] = cot;
	m->e[2][2] = -(far + near) / (far - near);
	m->e[3][2] = -(2.0f * far * near) / (far - near); 
	m->e[2][3] = -1; 
	m->e[3][3] = 0;
	
	
}


