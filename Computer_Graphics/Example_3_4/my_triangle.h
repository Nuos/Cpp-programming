#pragma once
#include "my_drawable.h"

class my_triangle : public my_drawable
{
public:
	float size;


	my_triangle(float newX, float newY, float newZ, float newSize, float newTheta) : my_drawable(newX, newY, newZ, newTheta) {
		size = newSize;
	};
	~my_triangle();

	void draw();
};

