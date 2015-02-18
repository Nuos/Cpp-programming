#include "StdAfx.h"
#include "flocking_agent.h"


flocking_agent::flocking_agent(my_drawable* shape, my_vector dir, float range, float max_vel)
{
	//a flocking agent is a physics object of a specified shape
	obj = new physics_object(5,shape);

	//it starts out moving in a specified direction
	obj->applyImpulse(dir.x,dir.y,dir.z);
	obj->rotate2D(obj->getVelocity());

	//it has a range of sight
	radius = range;

	//it does not have gravity, as it's a top-down representation
	obj->disableGravity();

	//it does not lose directional movement energy
	obj->setEnergyLoss(1.0);

	//it has a maximum velocity and force
	obj->setMaxVelocity(max_vel);

	colour = my_vector(255,0,0);
}


flocking_agent::~flocking_agent(void)
{
}

void flocking_agent::changeDirection(my_vector newDirection, float deltaTime) {
	//apply a force in the direction specified and advance the simulation
	obj->applyForce(newDirection.x, newDirection.y, newDirection.z); 
	obj->advance(deltaTime);
	obj->rotate2D(obj->getVelocity());
}

my_vector flocking_agent::getDistanceVector(flocking_agent* agent, int w_width, int w_height) {
	//get the distance between two agents, taking into account that the screen wraps around
	float xDist = obj->displacement.x - agent->obj->displacement.x;
	float yDist = obj->displacement.y - agent->obj->displacement.y;

	//calculate the distances if we wrapped around the screen
	float xDistAlt = w_width - xDist;
	float yDistAlt = w_height - yDist;

	//check if wrapped distance is shorter than regular distance
	//if(abs(xDistAlt) < abs(xDist))
	//	xDist = xDistAlt;
	//if(abs(yDistAlt) < abs(yDist))
	//	yDist = yDistAlt;

	return my_vector(xDist,yDist,0);
}

void flocking_agent::draw() {
	glPushMatrix();
		glColor3ub( colour.x, colour.y, colour.z);
		obj->draw();
	glPopMatrix();
}