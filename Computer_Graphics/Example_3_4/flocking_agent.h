#pragma once
#include "physics_object.h"

class flocking_agent
{
public:
	flocking_agent(my_drawable*, my_vector, float,float);
	~flocking_agent(void);

	inline my_vector getVelocity() { return obj->getVelocity(); }
	inline my_vector getDisplacement() { return obj->displacement; }
	inline void setDisplacement(my_vector newValue) { obj->displacement = newValue; }

	inline void draw() { obj->draw(); }

	void changeDirection(my_vector, float);
	my_vector getDistanceVector(flocking_agent*,int,int);

	float radius;
private:
	physics_object* obj;
};

