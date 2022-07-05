#include <stdio.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include "obj_loader.h"
#include "matrix.h"

#define SCREEN_W 640
#define SCREEN_H 480

model_t obj; 
vert_t src[9999];
static float rx, ry; 

void logic()
{
	/*matrix math, this arrangment is only for learning
      	if i feel motivated later i will develop a C lib for matrix stuff
      	enable commented lines to rotate z forever*/ 
      	
    matrix4_t m1, m2;
    //static float r = 0; 
    //r+=0.5f;
    //matrix_translate(m1, 0.0f, 0.0f, 1.0f);
    matrix_same_scale(&m1, 0.8f);
    matrix_rot_x(&m2, DEGTORAD(rx));
    matrix_matrix_mul(&m1, &m2);
    matrix_rot_y(&m2, DEGTORAD(ry));
    matrix_matrix_mul(&m1, &m2);
    //matrix_rot_z(&m2, DEGTORAD(r));
    //matrix_matrix_mul(&m1, &m2);
    matrix_translate(&m2, 0.0f, 0.0f, -1.7f);
    matrix_matrix_mul(&m1, &m2);
    //r+=0.1f;
    //if (r > 3)r =0; 
    //r = r%360;
    matrix_projection(&m2, 90, (float)SCREEN_W / (float)SCREEN_H, 0.1f, 1000.0f);
    matrix_matrix_mul(&m1, &m2);
    
    for(int i = 0; i < obj.vert_length; ++i)
    {
        matrix_vert_mul(&m1, &src[i], &obj.vert[i]);
    }
    
}

void passive_mouse(int x, int y)
{
	rx = -((y-SCREEN_H/2)*0.1f);
	ry = -(((x-SCREEN_W/2)*0.1f));
}

void keyboard(unsigned char key, int x, int y)
{
	/*escape key*/	
	if ((int)key == 27)glutDestroyWindow(glutGetWindow());
}

void display(void)
{   
	static float distance = 0;
	static float color = 0; 
	
    logic();
    
    /*this was here to test while developing matrix math*/
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 640.0f/480.0f, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glTranslatef(.0f, .0f, -3);
	glRotatef(-ry, 0.0f, 1.0f, 0.0f);
	glRotatef(-rx, 1.0f, 0.0f, 0.0f);
	for(int i = 0; i < obj.vert_length; ++i)
	{
		src[i] = obj.vert[i];
	}
	*/
	
	/*slowly i will try to remove openGL dependency to 
    	learn as much as i can about
		about computer graphics
	*/ 
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	/*fixed funtion used because this is for learning*/
	glBegin(GL_TRIANGLES);
	
		for(int i = 0; i < obj.face_length; ++i)
		{
			distance = src[obj.faces[i].vx-1].w;
			color = 1.0f/distance*0.5f; 

			glColor4f(color, color, color-0.5f, 1.0f);
			
		  	glVertex3f(src[obj.faces[i].vx-1].x, 
		               src[obj.faces[i].vx-1].y, 
		               src[obj.faces[i].vx-1].z);
		           
       		glVertex3f(src[obj.faces[i].vy-1].x, 
	    	           src[obj.faces[i].vy-1].y, 
	    	           src[obj.faces[i].vy-1].z);		          
		           
	    	glVertex3f(src[obj.faces[i].vz-1].x, 
	    	           src[obj.faces[i].vz-1].y, 
	    	           src[obj.faces[i].vz-1].z);	   	       
		}
		           
		          
	glEnd(); 
	glFlush();

	glDisable(GL_DEPTH_TEST);
	
	glutPostRedisplay();
}

void init(int a, char **b)
{
	glutInit(&a, b);
//	glutInitContextVersion(1, 3);
	
	glutInitWindowSize(SCREEN_W, SCREEN_H);
	glutInitWindowPosition(SCREEN_W / 2, SCREEN_H / 2);
	
	glutCreateWindow("OpenGL with glut");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(passive_mouse);
}

int main(int argc, char **argv)
{
	init(argc, argv);
	
	load_obj(argv[1], &obj);
	
	// glFrontFace(GL_CCW);
	glClearColor(0.0f, 0.3f, 0.0f, 1.0f);
	
	glutMainLoop();
	return 0;
}
