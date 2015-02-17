#pragma once
#include "my_particle.h"
#include <vector>

class my_emitter
{
public:
	my_emitter(float,float,float,int);
	~my_emitter(void);

	void update(float);
	void draw();

private:
	std::vector<my_particle*> *particles;
	float x,y,z;
	int noOfParticles;
	float generateMagnitude();
	float generateLifespan();
	float generateSize();
	void resetParticles(std::vector<my_particle*>);
};

