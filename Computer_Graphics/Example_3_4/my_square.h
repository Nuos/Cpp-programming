#pragma once
#include "my_drawable.h"

class my_square : public my_drawable
{
public:
	float size,theta;

	my_square(float newX, float newY, float newZ, float newSize, float newTheta) : my_drawable(newX,newY,newZ) {
		size = newSize;
		theta = newTheta;
	}
	~my_square(void);

	void draw();
};

