// Example_7_1.cpp : Using Rotation
//
// Author  : E. Angel, Interactive Computer Graphics
//           A Top-Down Approach with OpenGL, Third Edition
//           Addison-Wesley Longman, 2003
// Version : 1.1 - Commenting changed to match other examples style
//
// Demonstration of use of homogeneous coordinate transformations 
// and simple data structure for representing cube from Chapter 4 
// 
// Program behaviour:
// Left Mouse Button (LMB) spins the cube on its X-Axis
// Right Mouse Button (RMB) spins the cube on its Y-Axis
// Middle Mouse Button (MMB) spins the cube on its Z-Axis
//
// Callback commentary sent to normal command window.
//
// Last tested in Visual C++ 2010 Express 

#include "stdafx.h"
#include <stdlib.h>
#include <GL/glut.h>

//======================================================
// GLOBAL VARIABLES 
//======================================================
GLfloat vertices[][3] = 
{
	{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0},  {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
	{1.0,-1.0,1.0},  {1.0,1.0,1.0},   {-1.0,1.0,1.0}
};

GLfloat colors[][3] = {
	{0.0,0.5,0.5}, {1.0,0.0,0.0},
	{1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, 
	{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}
};

static GLfloat theta[] = {0.0, 0.0, 0.0}; // Rotation (X,Y,Z)
static GLint axis = 2; // Changed by the Mouse Callback Routine

//======================================================
// SHAPE CREATING ROUTINES
//======================================================
void polygon(int a, int b, int c , int d)
{
	// Draw a Polygon using the colour of the first vertex.
 	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube(void)
{
	// Create 6 Polygons for a cube.
	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(4,7,3,0);
	polygon(1,2,6,5);
	polygon(7,4,5,6);
	polygon(5,4,0,1);
}

//======================================================
// MOUSE CALLBACK ROUTINE
//======================================================
void mouseCallBack(int btn, int state, int x, int y)
{
	// Changes the rotation axis depending on the mouse button pressed.
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

//======================================================
// IDLE CALLBACK ROUTINE 
//======================================================
void idleCallBack()
{
	// Spins the cube around the set axis.
	theta[axis] += 0.5;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	glutPostRedisplay();
}

//======================================================
// WINDOW RESHAPE ROUTINE 
//======================================================
void displayReshape(int w, int h)
{
	// If the display is re-sized in any way, the cube is redrawn
	// so that it fits the display properly. Try it!

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
// DISPLAY CALL BACK ROUTINE 
//======================================================
void displayCallBack()	
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the Frame Buffer
	glLoadIdentity();									// Go back to the default identity matrix
	glRotatef(theta[0], 1.0, 0.0, 0.0);					// Rotate the cube
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	colorcube();										// Draw the cube

	glFlush();											
	glutSwapBuffers();									// Swap the buffers (due to double buffering)
}

//======================================================
// MAIN PROGRAM
//======================================================
int main(int argc, char** argv)
{
    // Allow cmd line arguments to be passed to the glut
	glutInit(&argc, argv);

	// Create and name window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Need both double buffering and z buffer
    glutInitWindowSize(500, 500);
    glutCreateWindow("Example 7.1 - Using Rotation on a Cube");

	// Add Display & Mouse CallBacks
    glutReshapeFunc(displayReshape);
    glutDisplayFunc(displayCallBack);
	glutIdleFunc(idleCallBack);
	glutMouseFunc(mouseCallBack);
	   
	// Enables the application to do tests on the depth and updates the buffer.
	glEnable(GL_DEPTH_TEST); 

	// Print information about the application in the command console 
	printf("Cube Rotation Example\nChange Axis of Rotation by pressing Left, Right or Middle Mouse Buttons\n\n");

	//Enter infinite loop calling 'displayCallBack'
    glutMainLoop();

	return 0;
}
