// Example_11_6.cpp : Rotating Textured Cube - Bitmap
//
// Author  : Mike Chantler
// Date    : 18/03/2007
// Version : 1.0
//
// Rotating Textured Cube using Bitmaps.
// Loads all the textures once on initialisation rather than in the drawing callback.
// Uses .bmp reader written by Michael Sweet (http://www.easysw.com/~mike/).
// ASSUMES all images are uncompressed .bmp 512x512
//
// Program behaviour:
// Mouse Click & Drag Changes View
// Key 'a' : Toggles Animation
// Key 'b' : Toggles Bi-Linear Interpretation
// Key 'B' : Sets the Texture Environment to be GL_BLEND
// Key 'M' : Sets the Texture Environment to be GL_MODULATE
// Key 'R' : Sets the Texture Environment to be GL_REPLACE
//
// Callback commentary sent to normal command window.
//
// Last tested in Visual C++ 2010 Express 

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "bitmap.h"
#include <String.h>

//======================================================
// GLOBAL VARIABLES 
//======================================================

//Should implement following as arrays but had problems with .bmp reader
BITMAPINFO *BitmapInfo;// bmp information 
GLubyte *BitmapBits;   // bmp data 

// View Variables
float pitch = 0.0f;
float yaw = 0.0f;
float pitch0, yaw0;
int MousePressed = 0;
int mouseX0, mouseY0;
int Animated = true;

// Texture Settings
int linear=false;
#define N_TEXTURES 6
GLuint textureHandle[N_TEXTURES];
char * filename[N_TEXTURES]={
	"assets/Image9.bmp", 
	"assets/Image10.bmp",
	"assets/Image11.bmp",
	"assets/Image12.bmp",
	"assets/Image13.bmp",
	"assets/Image14.bmp",
};

//======================================================
// CUBE ROUTINES
//======================================================

GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat colors[][4] = {{0.0,0.0,0.0,0.5},{1.0,0.0,0.0,0.5},
{1.0,1.0,0.0,0.5}, {0.0,1.0,0.0,0.5}, {0.0,0.0,1.0,0.5}, 
{1.0,0.0,1.0,0.5}, {1.0,1.0,1.0,0.5}, {0.0,1.0,1.0,0.5}};

void polygon(int a, int b, int c , int d, int textureNo)
{
	// Select texture to display
	glBindTexture(GL_TEXTURE_2D, textureHandle[textureNo]);

	// Set interpolation 
	if(linear)
	{
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	}

	// Draw a polygon via list of vertices
	glBegin(GL_POLYGON);
		glColor4fv(colors[a]); glTexCoord2f(1,0); glVertex3fv(vertices[a]);
		glColor4fv(colors[b]); glTexCoord2f(0,0); glVertex3fv(vertices[b]);
		glColor4fv(colors[c]); glTexCoord2f(0,1); glVertex3fv(vertices[c]);
		glColor4fv(colors[d]); glTexCoord2f(1,1); glVertex3fv(vertices[d]); 
	glEnd();
}

void drawTexturedCube(void){
	polygon(0,3,2,1,0);
	polygon(2,3,7,6,1);
	polygon(0,4,7,3,2);
	polygon(1,2,6,5,3);
	polygon(4,5,6,7,4);
	polygon(0,1,5,4,5);
}

//======================================================
// TEXTURE ROUTINES
//======================================================
void loadTextures()
{
	// Function to load textures into graphics card from .bmp images

	// Enable 2D texturing and get the necessary number of texture handles (or objects)
	glEnable(GL_TEXTURE_2D); 
	glGenTextures(N_TEXTURES, textureHandle);

	// Load textures into graphics card (note that these images are in BRG rather than RGB format)
	for (int i=0; i<N_TEXTURES; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textureHandle[i]);
		BitmapBits=NULL;

		//Grab memory, load image info and data and update pointers:
		BitmapBits = (GLubyte*) loadBMP(filename[i], &BitmapInfo); 	
		if (BitmapBits==NULL) printf("ERROR: Can't find file 0\n\n");
		else glTexImage2D(GL_TEXTURE_2D,0,3,512,512,0,GL_BGR_EXT,GL_UNSIGNED_BYTE, BitmapBits);
		free(BitmapBits); free(BitmapInfo); //Don't need memory for this image anymore
	}
}

//======================================================
// DISPLAY CALLBACK ROUTINE 
//======================================================
void displayCallBack(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glRotatef(yaw, 0.0f, 1.0f, 0.0f); //yaw about y-axis
    glRotatef(pitch, 1.0f, 0.0f, 0.0f); //pitch about x-axis 
	drawTexturedCube();
	glutSwapBuffers();
}

//======================================================
// IDLE CALLBACK ROUTINE 
//======================================================
void idleCallBack()
{
	if (!MousePressed && Animated) yaw += 1.0f;    
	glutPostRedisplay();
}

 
//======================================================
// MOUSE CALLBACK ROUTINES
//======================================================
void mouseButtonCallback(int button, int state, int x, int y)
{
    switch (state)  {
    case GLUT_DOWN:
        MousePressed = true;
        pitch0 = pitch; yaw0 = yaw;
        mouseX0 = x; mouseY0 = y;
        break;
    default:
    case GLUT_UP:
        MousePressed = false;
        break;
    }
} 

void mouseMotionCallback(int x, int y)
{
    pitch = pitch0 + (y - mouseY0);
    yaw = yaw0 + (x - mouseX0);
	glutPostRedisplay();
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
void keyboardCallBack(unsigned char key, int x, int y){
    switch (key) {
    case 'a':
        Animated = !Animated;
		if(Animated) glutIdleFunc(idleCallBack); else glutIdleFunc(NULL);
    break;
	case 'b':
		linear =!linear;
	break;
	case 'B':
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	break;
	case 'M':
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	break;
	case 'R':
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	break;
    case 'q': case 27:
        exit(0);
    break;
	}
	glutPostRedisplay();
} 

//======================================================
// MENU CALLBACK ROUTINE 
//======================================================
void menuCallBack(int item){
    keyboardCallBack((unsigned char) item, 0, 0);
} 

//======================================================
// LOAD MENU ROUTINE 
//======================================================
void loadMenu()
{
    glutCreateMenu(menuCallBack);
    glutAddMenuEntry("[a] Toggle animation", 'a');
	glutAddMenuEntry("[b] Toggle bi-linear interp.", 'b');
	glutAddMenuEntry("", 0); // add blank line
	glutAddMenuEntry("[B] GL_BLEND", 'B');
	glutAddMenuEntry("[M] GL_MODULATE", 'M');
	glutAddMenuEntry("[R] GL_REPLACE", 'R');
    glutAddMenuEntry("", 0); // add blank line
    glutAddMenuEntry("[q] Quit", 27);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
} 

//======================================================
// MAIN PROGRAM 
//======================================================
void main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Example 11.6 - Multi-Textured Cube using texture handles");

    glutReshapeFunc(reshapeCallBack);
    glutDisplayFunc(displayCallBack);
	glutMouseFunc(mouseButtonCallback);
	glutMotionFunc(mouseMotionCallback);
	glutKeyboardFunc(keyboardCallBack);	
	loadMenu();	

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2,0.2,0.2,1);
	loadTextures();

	// Print Application Usage
	printf("Program Controls:\n");
	printf("Mouse Click & Drag Changes View\n");
	printf("Key 'a' : Toggles Animation\n");
	printf("Key 'b' : Toggles Bi-Linear Interpretation\n");
	printf("Key 'B' : Sets the Texture Environment to be GL_BLEND\n");
	printf("Key 'M' : Sets the Texture Environment to be GL_MODULATE\n");
	printf("Key 'R' : Sets the Texture Environment to be GL_REPLACE\n");
	printf("\nThanks goes to Michael Sweet (http://www.easysw.com/~mike/) for bitmap.cpp.\n");
	
	glutMainLoop();
}

