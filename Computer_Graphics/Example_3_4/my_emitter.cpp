#include "StdAfx.h"
#include "my_emitter.h"
#include "my_vector.h"
#include "my_square.h"
#include <random>

my_emitter::my_emitter(float newX, float newY, float newZ, int noParticles)
{

	particles = new std::vector<my_particle*>();
	x = newX;
	y = newY;
	z = newZ;
	noOfParticles = noParticles;

	float degreeGap = 360/noOfParticles;
	for(int i = 0; i < noOfParticles; i++) {
		float direction = degreeGap*i*M_PI/180.0;

		//calculate the magnitude of the directional movement
		float magnitude = rand() % 50 + 20;

		float xDir = cos(direction)*magnitude;
		float yDir = sin(direction)*magnitude;
		my_vector* directionVector = new my_vector(xDir,yDir,0);
		my_particle* p = new my_particle(new my_square(x,y,z,0.5,0),255,directionVector);
		particles->push_back(p);
	}
}

void my_emitter::update(float deltaTime) {
	std::vector<my_particle*> vec = *particles;
	for(int i = 0; i < noOfParticles; i++) {
		vec[i]->update(deltaTime);
		if(vec[i]->isDead()) {
			//come up with new magnitude
			float magnitude = rand() % 50 + 20;
			vec[i]->reset(x,y,z,magnitude);
		}
	}
}

void my_emitter::draw() {
	std::vector<my_particle*> vec = *particles;
	for(int i =0; i < noOfParticles; i++) {
		vec[i]->draw();
	}
}

my_emitter::~my_emitter(void)
{
	delete particles;
}
