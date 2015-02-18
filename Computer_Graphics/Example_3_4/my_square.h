#pragma once
#include "my_drawable.h"

class my_square : public my_drawable
{
public:
	float size;

	my_square(float newX, float newY, float newZ, float newSize, float newTheta) : my_drawable(newX,newY,newZ,newTheta) {
		size = newSize;
	}
	~my_square(void);

	void draw();
};

