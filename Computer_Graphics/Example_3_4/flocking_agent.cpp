#include "StdAfx.h"
#include "flocking_agent.h"


flocking_agent::flocking_agent(my_drawable* shape, my_vector dir, float range, float max_vel)
{
	obj = new physics_object(5,shape);
	obj->applyImpulse(dir.x,dir.y,dir.z);
	radius = range;
	obj->disableGravity();
	obj->setEnergyLoss(1.0);
	obj->setMaxVelocity(max_vel);
}


flocking_agent::~flocking_agent(void)
{
}

void flocking_agent::changeDirection(my_vector newDirection, float deltaTime) {
	obj->applyImpulse(newDirection.x,newDirection.y,newDirection.z);
	obj->advance(deltaTime);
}

my_vector flocking_agent::getDistanceVector(flocking_agent* agent, int w_width, int w_height) {
	float xDist = abs(obj->displacement.x - agent->obj->displacement.x);
	float yDist = abs(obj->displacement.y - agent->obj->displacement.y);

	//calculate the distances if we wrapped around the screen
	float xDistAlt = w_width - xDist;
	float yDistAlt = w_height - yDist;
	if(xDistAlt < xDist)
		xDist = xDistAlt;
	if(yDistAlt < yDist)
		yDist = yDistAlt;

	return my_vector(xDist,yDist,0);
}