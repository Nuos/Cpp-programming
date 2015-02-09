#pragma once
#include "my_vector.h"
#include "my_drawable.h"

class physics_object
{
public:
	float BOUNCE_FACTOR;
	float ENERGY_LOSS;

	my_vector displacement;

	physics_object(float,my_drawable*);
	~physics_object(void);

	void advance(float);
	void draw();
	void bounce(int,int,int);

	void applyImpulse(float,float,float);
	void applyForce(float,float,float);

	void disableGravity();
	void enableGravity();
private:
	my_vector velocity,gravity,directional_force;
	float mass;

	my_drawable* obj;
};

