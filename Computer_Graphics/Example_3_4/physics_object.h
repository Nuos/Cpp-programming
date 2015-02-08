#pragma once
#include "my_vector.h"
#include "my_drawable.h"

class physics_object
{
public:
	my_vector displacement;

	physics_object(float,my_drawable*);
	~physics_object(void);

	void advance(float);
	void draw();
	void bounce(int,int,int);
private:
	my_vector velocity,gravity;
	float mass;

	my_drawable* obj;
};

