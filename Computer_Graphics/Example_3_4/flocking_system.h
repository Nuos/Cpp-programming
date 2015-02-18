#pragma once
#include "flocking_agent.h"
#include <vector>

class flocking_system
{
public:
	flocking_system(float,float,float,int);
	~flocking_system(void);

	void updateFlocking(float,int,int);

	//agent parameters
	float AGENT_SPEED;

	//swarming parameters
	float ALIGNMENT;
	float COHESION;
	float SEPARATION;

	//magnitude of steering in one step
	float MOVEMENT_MAGNITUDE;

	void draw();
private:
	std::vector<flocking_agent*>* agents;
};

