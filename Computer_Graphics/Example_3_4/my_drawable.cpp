#include "StdAfx.h"
#include "my_drawable.h"


my_drawable::my_drawable(float newX, float newY, float newZ, float newTheta)
{
	//interface for all drawable objects
	x = newX;
	y = newY;
	z = newZ;
	theta = newTheta;
}


my_drawable::~my_drawable(void)
{
}
