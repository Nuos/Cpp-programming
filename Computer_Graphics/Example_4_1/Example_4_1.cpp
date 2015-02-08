// Example_4_1.cpp : 2D Orthographic Projection Example
//
// Author  : Mike Chantler 
// Date    : 17/04/2003
// Version : 1.0
//
// This program defines a 2D orthographic projection space
// and draws some points in it
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
	glPointSize(10.0);
	
	// Draw some points
	glBegin(GL_POLYGON);    
		glColor3f(1.0, 1.0, 1.0); // white
		glVertex2f(-1.0,  1.0); 
		glVertex2f( 1.0,  1.0);        
		glVertex2f( 1.0, -1.0);  
		glVertex2f(-1.0, -1.0);
	glEnd();

	// Flush the buffer to force drawing of all objects thus far
	glFlush(); 
}

//======================================================
// MAIN PROGRAM
//======================================================
int main(int argc, char** argv)
{  
	// Allow cmd line arguments to be passed to the glut
	glutInit(&argc, argv);

	// Create and name window
	glutInitWindowPosition(500,100);
	glutInitWindowSize(500,500);	
	glutCreateWindow("Example 4.1 - 2D Orthographic Projection"); 	
	
	// Set viewing area 
	glMatrixMode(GL_PROJECTION);  // Switch to projection (viewing) matrix 
	glLoadIdentity();             // Set to identity matrix
	gluOrtho2D(-10, 10, -10, 10); // Define 2D projection space 
 	glMatrixMode(GL_MODELVIEW);   // Switch back to model matrix 
	
	// Clear Canvas
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Set initial colour to white
	glColor3f(1.0, 1.0, 1.0);
	
	// Add display callback
	glutDisplayFunc(displayCallBack);  
   
	// Print information about the application in the command console 
	printf("2D Orthographic Projection Example\nNo Interaction with this application possible.");

	// Enter infinite loop calling 'displayCallBack'
	glutMainLoop();

	return 0;
}
