// Example_2_1.cpp : Defines the entry point for the console application.
//
// Author  : Mike Chantler 
// Date    : 22/9/2009
// Version : 1.0
//
// Simple Hello World program for OpenGL 
//
// Last tested in Visual C++ 2010 Express 

#include "stdafx.h"
#include <GL/glut.h>

//======================================================
// DISPLAY CALL BACK ROUTINE 
//======================================================
void displayCallBack()
{
    // Clear the window
	glClear(GL_COLOR_BUFFER_BIT); 

	// Specify polygon to be drawn and vertices of polygon
	glBegin(GL_POLYGON);        
		glVertex2f(-0.5, -0.5);        
		glVertex2f(-0.5,  0.5);        
		glVertex2f( 0.5,  0.5);        
		glVertex2f( 0.5, -0.5);    
	glEnd();

	// Flush the buffer to force drawing of all objects thus far
	glFlush(); 
}

//======================================================
// MAIN PROGRAM
//======================================================
int _tmain(int argc, _TCHAR* argv[])
{
	// Create the Window
	glutCreateWindow("Example 2.1 - Simple OpenGL Example"); 
    
	// Assign displayCallBack() to be the function called whenever a display
	// event occurs, generally after a resize or expose event
	glutDisplayFunc(displayCallBack);  
	
	// Print information about the application in the command console 
	printf("OpenGL Console Output: Hello World\nNo Interaction with this application possible.");

	//Enter infinite loop calling 'displayCallBack'
	glutMainLoop();

	return 0;
}
