#include "StdAfx.h"
#include "my_square.h"


my_square::~my_square(void)
{
}

void my_square::draw() {
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(theta, 0, 0, 1.0);

		glBegin(GL_POLYGON);
			glVertex2f(size, size);
			glVertex2f(-size, size);
			glVertex2f(-size, -size);
			glVertex2f(+size, -size);
		glEnd();
	glPopMatrix();
}