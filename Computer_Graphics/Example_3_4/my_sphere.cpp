#include "StdAfx.h"
#include "my_sphere.h"


my_sphere::~my_sphere(void)
{
}

void my_sphere::draw() {
	printf("Sphere coordinates: %f,%f,%f\n",x,y,z);
	glPushMatrix();
		glTranslatef( x,y,z );
		glColor3d( 1, 0, 0);
		glutSolidSphere(radius, subdivisions,subdivisions);
	glPopMatrix();
}