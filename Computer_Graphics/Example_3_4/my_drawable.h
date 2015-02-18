#pragma once
class my_drawable
{
public:
	my_drawable(float,float,float,float);
	~my_drawable(void);

	float x,y,z, theta;

	virtual void draw() = 0;
};

