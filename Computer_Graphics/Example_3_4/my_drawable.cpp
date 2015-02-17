#include "StdAfx.h"
#include "my_drawable.h"


my_drawable::my_drawable(float newX, float newY, float newZ)
{
	//interface for all drawable objects
	x = newX;
	y = newY;
	z = newZ;
}


my_drawable::~my_drawable(void)
{
}
