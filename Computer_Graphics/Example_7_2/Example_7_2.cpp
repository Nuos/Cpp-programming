// Example_7_2.cpp : Using Rotation with Vertex Arrays
//
// Author  : E. Angel, Interactive Computer Graphics
//           A Top-Down Approach with OpenGL, Third Edition
//           Addison-Wesley Longman, 2003
// Version : 1.1 - Commenting changed to match other examples style
//
// Using Vertex Arrays 
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

	GLfloat vertices[] = 
	{-1.0,-1.0,-1.0,
	  1.0,-1.0,-1.0,
	  1.0,1.0,-1.0,
	 -1.0,1.0,-1.0, 
	 -1.0,-1.0,1.0, 
	  1.0,-1.0,1.0, 
	  1.0,1.0,1.0, 
	 -1.0,1.0,1.0};

	GLfloat colors[] = 
	{0.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,1.0,0.0, 
	0.0,1.0,0.0, 
	0.0,0.0,1.0, 
	1.0,0.0,1.0, 
	1.0,1.0,1.0, 
	0.0,1.0,1.0};

    // define cube faces
	// each set of 4 indices indicates a different face
	GLubyte cubeIndices[]=
	{0,3,2,1,
	2,3,7,6,
	0,4,7,3,
	1,2,6,5,
	4,5,6,7,
	0,1,5,4};

static GLfloat theta[] = {0.0, 0.0, 0.0}; // Rotation (X,Y,Z)
static GLint axis = 2; // Changed by the Mouse Callback Routine

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
        glOrtho(-4.0, 4.0, -3.0 * (GLfloat) h / (GLfloat) w,
            5.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -3.0, 5.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

//======================================================
// DISPLAY CALL BACK ROUTINE 
//======================================================
void displayCallBack()	
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
	glTranslatef(0.0, 3.0, 0.0);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	// Now draw the cube
    glColorPointer(3,GL_FLOAT, 0, colors); 
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

	glutSwapBuffers(); 
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
    glutCreateWindow("Example 7.2 - Vertex Arrays");

	// Add Display & Mouse CallBacks
    glutReshapeFunc(displayReshape);
    glutDisplayFunc(displayCallBack);
	glutIdleFunc(idleCallBack);
	glutMouseFunc(mouseCallBack);

	glShadeModel(GL_FLAT); //use one colour per face
    glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
 	glEnableClientState(GL_COLOR_ARRAY); 
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3,GL_FLOAT, 0, colors); 
	glClearColor(0.0,0.0,0.0,1.0);
	glColor3f(0.0,0.0,0.0);

	// Print information about the application in the command console 
	printf("Cube Rotation & Vertex Array Example\nChange Axis of Rotation by pressing Left, Right or Middle Mouse Buttons\n\n");

	//Enter infinite loop calling 'displayCallBack'
    glutMainLoop();

	return 0;
}
