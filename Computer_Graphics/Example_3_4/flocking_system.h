#pragma once
#include "flocking_agent.h"
#include <vector>

class flocking_system
{
public:
	flocking_system(float,float,float,int);
	~flocking_system(void);

	void updateFlocking(float,int,int);

	float AGENT_SPEED;
	float ALIGNMENT;
	float COHESION;
	float SEPARATION;

	void draw();
private:
	std::vector<flocking_agent*>* agents;
};

