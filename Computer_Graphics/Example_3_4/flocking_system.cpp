#include "StdAfx.h"
#include "flocking_system.h"
#include "my_square.h"

flocking_system::flocking_system(float newX, float newY, float newZ, int noOfAgents)
{
	AGENT_SPEED = 200;
	ALIGNMENT = 0.0;
	COHESION = 0.0;
	SEPARATION = 1;
	agents = new std::vector<flocking_agent*>();

	for(int i = 0; i < noOfAgents; i++) {
		float xPos = rand() % 50 + newX;
		float yPos = rand() % 50 + newY;
		float angle = (rand() % 360)*M_PI/180.0;
		float xDir = cos(angle)*AGENT_SPEED;
		float yDir = sin(angle)*AGENT_SPEED;
		my_vector directionVector = my_vector(xDir,yDir,0);

		flocking_agent* a = new flocking_agent(new my_square(xPos,yPos,newZ,1.0,0),directionVector,70, AGENT_SPEED);

		agents->push_back(a);
	}
}


flocking_system::~flocking_system(void)
{
	delete agents;
}

void flocking_system::draw() {
	std::vector<flocking_agent*> agentArray = *agents;

	for(int i = 0; i < agentArray.size(); i++) {
		agentArray[i]->draw();
	}
}

void flocking_system::updateFlocking(float deltaTime, int w_width, int w_height) {
	std::vector<flocking_agent*> agentArray = *agents;

	for(int i = 0; i < agentArray.size(); i++) {
		flocking_agent* a1 = agentArray[i];
		
		int neighbourCount = 0;
		my_vector alignment = my_vector(0,0,0);
		my_vector cohesion = my_vector(0,0,0);
		my_vector separation = my_vector(0,0,0);

		for(int j = 0; j < agentArray.size(); j++) {
			if(i == j)
				continue;
			flocking_agent* a2 = agentArray[j];
			if(a1->getDistanceVector(a2,w_width,w_height).length() < a1->radius) {
				//compute alignment
				alignment.x += a2->getVelocity().x;
				alignment.y += a2->getVelocity().y;

				//compute cohesion
				cohesion.x += a2->getDisplacement().x;
				cohesion.y += a2->getDisplacement().y;

				//compute separation
				separation.x += a2->getDisplacement().x - a1->getDisplacement().x;
				separation.y += a2->getDisplacement().y - a1->getDisplacement().y;

				neighbourCount++;
			}
		}
		if(neighbourCount != 0) {
			//compute alignment
			alignment.x = alignment.x / neighbourCount;
			alignment.y = alignment.y / neighbourCount;
			alignment = *alignment.normalise();

			//compute cohesion
			cohesion.x = cohesion.x / neighbourCount;
			cohesion.y = cohesion.y / neighbourCount;
			cohesion = my_vector(cohesion.x - a1->getDisplacement().x, cohesion.y - a1->getDisplacement().y,0);
			cohesion = *cohesion.normalise();

			//compute separation
			separation.x = separation.x / neighbourCount;
			separation.y = separation.y / neighbourCount;
			separation.x *= -1;
			separation.y *= -1;
			separation = *separation.normalise();

			
			my_vector vec = alignment*ALIGNMENT + cohesion*COHESION + separation*SEPARATION;
			vec = vec*AGENT_SPEED;

			a1->changeDirection(vec, deltaTime);
		}

		//check screen boundaries
		my_vector displacement = a1->getDisplacement();
		if(displacement.x > w_width)
			a1->setDisplacement(my_vector(0,displacement.y,displacement.z));
		if(displacement.x < 0)
			a1->setDisplacement(my_vector(w_width,displacement.y,displacement.z));
		if(displacement.y > w_height)
			a1->setDisplacement(my_vector(displacement.x,0,displacement.z));
		if(displacement.y < 0)
			a1->setDisplacement(my_vector(displacement.x,w_height,displacement.z));
	}

	
}
