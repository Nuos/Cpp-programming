#pragma once
class my_drawable
{
public:
	my_drawable(float,float,float);
	~my_drawable(void);

	float x,y,z;

	virtual void draw() = 0;
};

