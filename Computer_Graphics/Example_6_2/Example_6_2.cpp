// Example_6_2.cpp : Using Rotation
//
// Author  : Mike Chantler
// Date    : 03/05/2003
// Version : 1.1 - Addition of Pop/Push to main and Titles to printModelViewMatrix (Stuart Davidson - 30/08/2010)
//
// This program uses Translation to draw a Triangle and a Square
// then Rotation to rotate the shapes.
// 
// Program behaviour:
// Any keyboard key press, or LMB click-drag of the mouse, will rotate the shapes.
//
// Callback commentary sent to normal command window.
//
// Last tested in Visual C++ 2010 Express 

#include "stdafx.h"
#include <GL/glut.h>
#include <stdio.h>

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY keyboard(), motion()
//======================================================
GLfloat	theta;					// Rotation Angle ( NEW )


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
// KEYBOARD and MOTION CALLBACK ROUTINES
//======================================================
void keyboard(unsigned char key, int x, int y)
{
	printf("\nKeyboard call back: key=%c, x=%d, y=%d\n", key, x, y);
	theta+=5.0f;		// Increase The Rotation Variable 
	glutPostRedisplay();
}

void motion(int x, int y)
{
	theta+=5.0f;		// Increase The Rotation Variable
	glutPostRedisplay();
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
	printf("\nDISPLAY CALLED");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	// Rotate about Y axis ( NEW )
	glRotatef(theta,0.0f,1.0f,0.0f);
	glPushMatrix();										// Push the Rotated Matrix onto the Stack to use after drawing the triangle
	printModelViewMatrix("After Rotation");
	
	glTranslatef(-1.5f,0.0f, 0.0f);						// Move Left 1.5 Units from the Default Position
	
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
		glColor3f(0.0f,1.0f,0.0f);						// Green 
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle

	glPopMatrix();										// Removes the last matrix (Translation of -1.5)
	glTranslatef(1.5f,0.0f,0.0f);						// Moves Right 1.5 from the Default Position
	printModelViewMatrix("After 1st Translation");		

	glBegin(GL_QUADS);									// Draw A blue Quad
		glColor3f(0.5f,0.5f,1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
		glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glEnd();											// Done Drawing The Quad

	printf("\nRotation Angle = %.1f", theta);

	glutSwapBuffers();
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
	glutCreateWindow("Example 6.2 - Use of Rotation and Translation"); 	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

	// Set viewing area 
	glMatrixMode(GL_PROJECTION);  // Switch to projection (viewing) matrix 
	glLoadIdentity();             // Set to identity matrix
	glOrtho(-3, 3, -3, 3, 3, -3); // Define projection space 
 	glMatrixMode(GL_MODELVIEW);   // Switch back to model matrix 

	//Clear canvas
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//Set initial colour to white
	glColor3f(1.0, 1.0, 1.0);

	//Add display & kb callbacks
	glutDisplayFunc(displayCallBack); 
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);
   
	// Print information about the application in the command console 
	printf("Matrix Rotation Example\nRotate the shapes with any key press or click-drag of mouse.\n\n");

	//Enter infinite loop calling 'displayCallBack'
	glutMainLoop();

	return 0;
}
