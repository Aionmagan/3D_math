#ifndef __MATRIX_4__
#define __MATRIX_4__

#define PI 3.14159
#define DEGTORAD(x) (x * (PI / 180))

//#include "vector.h"
#include "obj_loader.h"

/*this is the hard way of using matrix*/ 
typedef struct
{
	float e[4][4]; 
}matrix4_t;

void matrix_identity(matrix4_t *m);

/*change this later to vec4*/
void matrix_vert_mul(matrix4_t *m, vert_t *des, vert_t *src);
void matrix_matrix_mul(matrix4_t *m1, matrix4_t *m2);

void matrix_translate(matrix4_t *m, float x, float y, float z);

/*this calls matrix_scale with 1 value for all*/
void matrix_same_scale(matrix4_t *m, float s);
void matrix_scale(matrix4_t *m, float x, float y, float z);


/*use radian "DEGTORAD"*/ 
void matrix_rot_x(matrix4_t *m, float rad);
void matrix_rot_y(matrix4_t *m, float rad);
void matrix_rot_z(matrix4_t *m, float rad);

/*project the perspective*/
void matrix_projection(matrix4_t *m, float fov, float aspect, float near, float far);
 
#endif //__MATRIX_4__
