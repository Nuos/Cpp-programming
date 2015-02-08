// Example_6_1.cpp : Using Translation
//
// Author  : Mike Chantler
// Date    : 03/05/2003
// Version : 1.1 - Addition of Pop/Push to main and Titles to printModelViewMatrix (Stuart Davidson - 30/08/2010)
//
// This program uses Translation to draw a Triangle and a Square
// 
// Callback commentary sent to normal command window.
//
// Last tested in Visual C++ 2010 Express 

#include "stdafx.h"
#include <GL/glut.h>
#include <stdio.h>

//======================================================
// Model View Matrix Printing Routine
//======================================================
void printModelViewMatrix(char *title)
{
	GLdouble modelview[16];                            
	int i;

	//Get the matrix back (16 values - see gl/get.html)
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	printf ("\tModelview matrix: %s\n", title);
	for (i=0; i<4; i++) 
		printf("\t%.1f\t%.1f\t%.1f\t%.1f\n", 
		modelview[i], modelview[i+4], modelview[i+8], modelview[i+12]);
}

//======================================================
// DISPLAY CALL BACK ROUTINE 
//======================================================
void displayCallBack()	
// This function was taken from lesson 2 nehe.gamedev.net:
/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */			    					
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	printModelViewMatrix("Inital Default Matrix");							

	glPushMatrix();										// Save a copy of the current Matrix (currently default) to the stack
														// so that we can go back to it later on.

														// Now we create a new Matrix...
	glTranslatef(-1.5f,0.0f, 0.0f);						// Move Left 1.5 Units (The translate function also adds the new translated matrix to the stack automatically)
	printModelViewMatrix("After 1st Translation");

	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle

	glPopMatrix();										// Remove the New Matrix from the stack 
	printModelViewMatrix("After Stack Pop");			// so we are starting back from the saved default matrix again.		

	glTranslatef(1.5f,0.0f,0.0f);						// Move Right 1.5 Units 
	printModelViewMatrix("After 2nd Translation");

	glBegin(GL_QUADS);									// Draw A Quad
		glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
		glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glEnd();											// Finished Drawing The Quad
	glFlush();
}


//======================================================
// MAIN PROGRAM
//======================================================
int main(int argc, char** argv)
{
	//Allow cmd line arguments to be passed to the glut
	glutInit(&argc, argv);

	//Create and name window
	glutInitWindowPosition(500,100);
	glutInitWindowSize(500,500);	
	glutCreateWindow("Example 6.1 - Using Translation"); 	
	
	// Set viewing area 
	glMatrixMode(GL_PROJECTION);  // Switch to projection (viewing) matrix 
	glLoadIdentity();             // Set to identity matrix
	glOrtho(-5, 5, -5, 5, 5, -5); // Define projection space 
 	glMatrixMode(GL_MODELVIEW);   // Switch back to model matrix 

	//Clear canvas
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//Set initial colour to white
	glColor3f(1.0, 1.0, 1.0);

	//Add display callback
	glutDisplayFunc(displayCallBack);  

	// Print information about the application in the command console 
	printf("Matrix Translation Example\nNo Interaction with this application possible.\n\n");
   
	//Enter infinite loop calling 'displayCallBack'
	glutMainLoop();

	return 0;
}
