// Example_11_1.cpp : Rotating Texture Cube
//
// Author  : E. Angel, Interactive Computer Graphics
//           A Top-Down Approach with OpenGL, Third Edition
//           Addison-Wesley Longman, 2003
//
// Rotating Texture Cube
//
// Program behaviour:
// Left Mouse Button (LMB) spins the cube on its X-Axis
// Right Mouse Button (RMB) spins the cube on its Y-Axis
// Middle Mouse Button (MMB) spins the cube on its Z-Axis
// Key '1' : Starts Rotation
// Key '2' : Ends Rotation
// Key 'a' : GL_LINEAR Texture
// Key 's' : GL_NEAREST Texture
//
// Callback commentary sent to normal command window.
//
// Last tested in Visual C++ 2010 Express 

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

//======================================================
// GLOBAL VARIABLES 
//======================================================

GLfloat planes[]= {-1.0, 0.0, 1.0, 0.0};
GLfloat planet[]= {0.0, -1.0,  0.0, 1.0};

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;

//======================================================
// CUBE ROUTINES
//======================================================

GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat colors[][4] = {{0.0,0.0,0.0,0.5},{1.0,0.0,0.0,0.5},
{1.0,1.0,0.0,0.5}, {0.0,1.0,0.0,0.5}, {0.0,0.0,1.0,0.5}, 
{1.0,0.0,1.0,0.5}, {1.0,1.0,1.0,0.5}, {0.0,1.0,1.0,0.5}};

void polygon(int a, int b, int c , int d)
{
	glBegin(GL_POLYGON);
		glColor4fv(colors[a]);
		glTexCoord2f(0.0,0.0); 
		glVertex3fv(vertices[a]);
		glColor4fv(colors[b]);
		glTexCoord2f(0.0,1.0);
		glVertex3fv(vertices[b]);
		glColor4fv(colors[c]);
		glTexCoord2f(1.0,1.0); 
		glVertex3fv(vertices[c]);
		glColor4fv(colors[d]);
		glTexCoord2f(1.0,0.0); 
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube(void)
{
	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(0,4,7,3);
	polygon(1,2,6,5);
	polygon(4,5,6,7);
	polygon(0,1,5,4);
}

//======================================================
// DISPLAY CALLBACK ROUTINE 
//======================================================
void displayCallBack(void)
{
// Clear frame buffer and z buffer,
// Rotate Cube and Draw, swap buffers 

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	colorcube();
	glutSwapBuffers();
}

//======================================================
// IDLE CALLBACK ROUTINE 
//======================================================
void idleCallBack()
{
	// Idle callback, spin cube 2 degrees about selected axis
	theta[axis] += 0.2;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	glutPostRedisplay();
}

//======================================================
// MOUSE CALLBACK ROUTINES
//======================================================
void mouseCallBack(int btn, int state, int x, int y)
{
	// Selects the Axis to Rotate around.
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

//======================================================
// DISPLAY RESHAPE CALLBACK ROUTINE 
//======================================================
void reshapeCallBack(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

//======================================================
// KEYBOARD CALLBACK ROUTINES 
//======================================================
void keyboardCallBack(unsigned char k, int x, int y)
{
	if(k == '1') glutIdleFunc(idleCallBack);
	if(k == '2') glutIdleFunc(NULL);
	if(k == 'q') exit(0);
	if(k == 'a') {glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); printf("\nLinear");}
	if(k == 's') {glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); printf("\nNearest");}
}

//======================================================
// MAIN PROGRAM 
//======================================================
void main(int argc, char **argv)
{
	// Set up texture image
	GLubyte image[64][64][3];
	int i, j, r, c;
	for(i=0;i<64;i++)
	{
	 for(j=0;j<64;j++)
	 {
	   c = ((((i&0x1)==0)^((j&0x16))==0))*255;
	   image[i][j][0]= (GLubyte) c;
	   image[i][j][1]= (GLubyte) c;
	   image[i][j][2]= (GLubyte) c;
	 }
	}
   
	// Create and Name window
	// Add Display & Mouse CallBacks
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Example 11.1 - Rotating Textured Cube");
    glutReshapeFunc(reshapeCallBack);
    glutDisplayFunc(displayCallBack);
	glutMouseFunc(mouseCallBack);
	glutKeyboardFunc(keyboardCallBack);
	glEnable(GL_DEPTH_TEST);

	// Set up texture
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D,0,3,64,64,0,GL_RGB,GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
	glClearColor(1.0,1.0,1.0,1.0);

	// Print Application Usage
	printf("Program Controls:\n");
	printf("Change Axis of Rotation by pressing Left, Right or Middle Mouse Buttons\n");
	printf("Key \"1\" : Starts Idle Rotation.\n");
	printf("Key \"2\" : Stops Idle Rotation.\n");
	printf("Key \"a\" : Sets Texture to GL_LINEAR.\n");
	printf("Key \"s\" : Sets Texture to GL_NEAREST.\n");

	//Enter infinite loop calling 'displayCallBack'
	glutMainLoop();
}
