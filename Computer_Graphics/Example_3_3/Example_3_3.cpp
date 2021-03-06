// Example_3_3.cpp : Idle Function & Animation Example
//
// Author  : Mike Chantler 
// Date    : 18/3/07
// Version : 1.03: Timer function removed.
//
// This program illustrates the use of the glut library for
// animation using the idle function
//
// Program behaviour:
// Left Mouse Button & Drag - draws the square at mouse location when held down. 
// Right Mouse Button - exits the program
// Key "I" - Enables idle callbacks
// Key "i" - Disables idle callbacks
// Key "r" - Rotates square
// TimerCallback function - moves yellow square back and forwards across screen
// 
// Callback commentary sent to normal command window.
//
// Last tested in Visual C++ 2010 Express 


#include "stdafx.h" //not required for linux
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

//======================================================
// CONSTANTS 
//======================================================
// Square size
#define size 50.0

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY reshapeCallBack( )
//======================================================
// Window size
int w_height=800;
int w_width=800;

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY displayCallBack( )
//======================================================
int display_count=0; //keeps count of invocations

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY keyboardCallBack( )
//======================================================
float theta =0.0; // Rotation angle of square 
int timer_period_in_ms=100; // time between timer callbacks in milliseconds

//====================================================================
// GLOBAL VARIABLES WRITTEN TO BY motionCallBack( )
//====================================================================
int square_x, square_y; // position of square
int square_dx = 1; // incremental change insquare_x



//======================================================
// IDLE CALLBACK ROUTINE 
//======================================================
void idleCallBack()
{
	square_x += square_dx; //Increment x-position of square
	if (square_x > w_width || square_x ==0) square_dx *= -1; //Reverse direction if at edges

	glutPostRedisplay();
}

//======================================================
// RESHAPE CALLBACK ROUTINE
//======================================================
void reshapeCallback (int width, int height)
{
	//Update globals containing window size
	w_width=width;
	w_height=height;
}

//======================================================
// MOUSE MOTION CALLBACK ROUTINE 
//======================================================
void motionCallBack(int x, int y)
{
	printf("YYYMotion call back: %d, %d)\n", x, y);
	//Set square's location to current mouse position
	square_x = x;
	square_y = w_height-y; //Invert mouse y (as its measured from top)

	glutPostRedisplay();
}

//======================================================
// MOUSE CALLBACK ROUTINE 
//======================================================
void mouseCallBack(int btn, int state, int x, int y)
{
	printf("Mouse call back: button=%d, state=%d, x=%d, y=%d\n", btn, state, x, y);
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)   exit(0);
}

//======================================================
// KEYBOARD CALLBACK ROUTINE 
//======================================================
void keyboardCallBack(unsigned char key, int x, int y)
{
	printf("Keyboard call back: key=%c, x=%d, y=%d, theta=%f\n", key, x, y, theta);
	switch(key)
	{
	case 'I':
		glutIdleFunc(idleCallBack);
		printf("Idle function ON\n");
	break;
	case 'i':
		glutIdleFunc(NULL);
		printf("Idle function OFF\n");
	break;
	case 'r':
		theta = theta + 10.0;
	break;
	default:
		printf("Press i (Idle Off), I (Idle ON) or r (Rotate)");
	}

	glutPostRedisplay();
}


//======================================================
// DISPLAY CALL BACK ROUTINE 
//======================================================
void displayCallBack(void)
{	
	printf("Display call back %d\n", display_count++);

	glClearColor (0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	glTranslatef(square_x, square_y, 0.0);
	glRotatef(theta, 0, 0, 1.0);

	glBegin(GL_POLYGON);
		glColor3ub( 255, 255, 0);
		glVertex2f(size, size);
		glVertex2f(-size, size);
		glVertex2f(-size, -size);
		glVertex2f(+size, -size);
	glEnd();

	
	//Swap double buffers 
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
	glutInitWindowPosition(10,10);
	glutInitWindowSize(w_width,w_height);	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Example 3.3 - Basic Animation, Keyboard/Mouse and Glut Idle Libraries");

	// Set Projection Mode and Volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w_width , 0.0, w_height , -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	// Set clear color to black and clear window 
	glClearColor (1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

	// Set up callbacks
	glutMouseFunc (mouseCallBack);
	glutKeyboardFunc(keyboardCallBack);
	glutMotionFunc(motionCallBack);
	glutDisplayFunc(displayCallBack);
	glutReshapeFunc(reshapeCallback);

	// Print Application Usage
	printf("Program Controls:\n");
	printf("Left Mouse Button & Drag - Draws the square at mouse location.\n");
	printf("Right Mouse Button - Exits the program.\n");
	printf("Key \"I\" - Enables idle callbacks.\n");
	printf("Key \"i\" - Disables idle callbacks.\n");
	printf("Key \"r\" - Rotates square.\n");

	// Enter main event loop
	glutMainLoop();
}
