#include "stdafx.h"
#include "my_triangle.h"

my_triangle::~my_triangle()
{
}

void my_triangle::draw() {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(theta, 0, 0, 1.0);
		glBegin(GL_POLYGON);
			glVertex2f(0, size*3);
			glVertex2f(-size, -size);
			glVertex2f(+size, -size);
		glEnd();
	glPopMatrix();
}