// Example_3_4.cpp : Bouncing Square Answer
//
// Author  : Stuart Davidson
// Date    : 30/08/2010
// Version : 1.0
//
// This program displays the answer to the "Bouncing Square" application problem.
// For further comments on the code, refer to Example 3_3. 
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
#include "my_sphere.h"
#include "physics_object.h"
#include "my_emitter.h"
#include <ctime>
#include "flocking_system.h"

//======================================================
// CONSTANTS 
//======================================================
// Square size
#define size 50.0

//REFERENCE TO OBJECTS IN DEMO
physics_object* physics_obj;
my_emitter* particle_system;
flocking_system* flock;

//TIME TRACKER
clock_t prevTime;

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY reshapeCallBack( )
//======================================================
// Window size
int w_height=800;
int w_width=800;

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY displayCallBack( )
//======================================================
int display_count=0; 

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY keyboardCallBack( )
//======================================================
float theta =0.0; 
int timer_period_in_ms=100; 

//====================================================================
// GLOBAL VARIABLES WRITTEN TO BY motionCallBack( )
//====================================================================
int square_x, square_y; 
int square_dx = 1; 
int square_dy = 1; // Incremental Rate Change for square_y - *** New for Solution ***


//======================================================
// IDLE CALLBACK ROUTINE 
//======================================================
float getTime() {
	//generate the time elapsed from last physics step - used for making physics consistent with system clock
	clock_t currTime = clock();

	//check if it's our first tick
	if(prevTime == NULL) {
		prevTime = currTime;
	}
	clock_t deltaTime = currTime - prevTime;
	prevTime = currTime;
	
	float delta = ((float)deltaTime)/CLOCKS_PER_SEC;

	return delta;
}

void bouncingBallCallback() {
	
	//get delta time
	float delta = getTime();

	//advance the ball
	physics_obj->advance(delta);

	//collisions
	if (physics_obj->displacement.x > w_width) {
		physics_obj->bounce(-1,1,1); // Reverse direction if at width edges (as the change is on the X-Axis)
		physics_obj->displacement.x = w_width;
	}
	else if(physics_obj->displacement.x < 0) {
		physics_obj->bounce(-1,1,1); // Reverse direction if at width edges (as the change is on the X-Axis)
		physics_obj->displacement.x = 0;
	}
	if (physics_obj->displacement.y > w_height) {
		physics_obj->bounce(1,-1,1); // Reverse direction if at height edges (as the change is on the Y-Axis) - *** New for Solution ***
		physics_obj->displacement.y = w_height;
	}
	else if(physics_obj->displacement.y < 0) {
		physics_obj->bounce(1,-1,1); // Reverse direction if at height edges (as the change is on the Y-Axis) - *** New for Solution ***
		physics_obj->displacement.y = 0;
	}

	glutPostRedisplay();
}

void particleSystemCallback()
{
	float delta = getTime();
	
	//just advance the particle system
	particle_system->update(delta);
	
	glutPostRedisplay();
}

void flockingSystemCallback()
{
	float delta = getTime();
	
	//advance the flocking system
	flock->updateFlocking(delta,w_width,w_height);
	
	glutPostRedisplay();
}

void preDraw() {
	printf("Display call back %d\n", display_count++);

	glClearColor (0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
}

void postDraw() {
	//Swap double buffers 
	glutSwapBuffers();
}

//======================================================
// DISPLAY CALL BACK ROUTINE 
//======================================================
void bouncingBallDraw(void)
{	
	preDraw();

	physics_obj->draw();

	postDraw();
}

void particleSystemDraw(void)
{
	preDraw();
	
	particle_system->draw();

	postDraw();
}

void flockingSystemDraw(void)
{
	preDraw();

	flock->draw();

	postDraw();
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
	case 'B':
		//ball demo
		prevTime = NULL;
		delete physics_obj;
		physics_obj = new physics_object(0.5,new my_sphere(400,400,-50,50,50));
		glutIdleFunc(bouncingBallCallback);
		glutDisplayFunc(bouncingBallDraw);
	break;
	case 'P':
		//particle demo
		prevTime = NULL;
		delete particle_system;
		particle_system = new my_emitter(400,400,0,360);
		glutIdleFunc(particleSystemCallback);
		glutDisplayFunc(particleSystemDraw);
	break;
	case 'F':
		//flocking demo
		prevTime = NULL;
		delete flock;
		flock = new flocking_system(400,400,0,50);
		glutIdleFunc(flockingSystemCallback);
		glutDisplayFunc(flockingSystemDraw);
	break;
	case 'S':
		glutIdleFunc(NULL);
	default:
		printf("Unknown command.\n");
	}

	glutPostRedisplay();
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
	glutCreateWindow("Computer Games Programming Lab exercises");

	// Set Projection Mode and Volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w_width , 0.0, w_height , -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	// Set clear color to black and clear window 
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

	glEnable (GL_BLEND);

	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// Set up callbacks
	glutMouseFunc (mouseCallBack);
	glutKeyboardFunc(keyboardCallBack);
	glutMotionFunc(motionCallBack);
	glutReshapeFunc(reshapeCallback);

	// Print Application Usage
	printf("Program Controls:\n");
	printf("Right Mouse Button - Exits the program.\n");
	printf("B key - demonstrates the bouncing ball.\n");
	printf("P key - demonstrates the particle system.\n");
	printf("F key - demonstrates the flocking behaviour.\n");

	// Enter main event loop
	glutMainLoop();
}
