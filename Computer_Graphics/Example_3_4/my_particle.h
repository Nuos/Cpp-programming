#pragma once
#include "my_drawable.h"
#include "physics_object.h"

class my_particle
{
public:
	my_particle(my_drawable*, float, my_vector);
	~my_particle(void);

	void update(float);
	void draw();

	void reset(float,float,float,float);

	inline bool isDead() { return lifespan <= 0; };

private:
	float lifespan, lifespanMax;	
	physics_object* obj;
	my_vector direction;
};

