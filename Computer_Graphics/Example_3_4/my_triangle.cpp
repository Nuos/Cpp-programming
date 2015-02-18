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
			float sizeNew = size*1.0 / 2.0;
			glVertex2f(sizeNew, size * 2);
			glVertex2f(-size, -size);
			glVertex2f(+size, -size);
		glEnd();
	glPopMatrix();
}
