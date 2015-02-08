#pragma once
#include "my_drawable.h"

class my_sphere : public my_drawable
{
public:

	my_sphere(float newX, float newY, float newZ, float newRadius,int subdivs) : my_drawable(newX,newY,newZ) {
		radius = newRadius;
		subdivisions = subdivs;
	};
	~my_sphere(void);

	void draw();
private:
	float radius;
	int subdivisions;
};

