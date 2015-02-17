#include "StdAfx.h"
#include "my_emitter.h"
#include "my_vector.h"
#include "my_square.h"
#include <random>

my_emitter::my_emitter(float newX, float newY, float newZ, int noParticles)
{
	//instantiate globals
	particles = new std::vector<my_particle*>();
	x = newX;
	y = newY;
	z = newZ;
	noOfParticles = noParticles;

	//generate particles in a circular fashion
	float degreeGap = 360.0/noOfParticles;
	for(int i = 0; i < noOfParticles; i++) {
		//calculate the direction of a particle
		float direction = degreeGap*i*M_PI/180.0;

		//calculate the magnitude of the directional movement
		float magnitude = generateMagnitude();

		//get the direction vertor amplified by a random speed
		float xDir = cos(direction)*magnitude;
		float yDir = sin(direction)*magnitude;
		my_vector directionVector = my_vector(xDir,yDir,0);

		//generate a particle of random size, lifespan and speed
		my_particle* p = new my_particle(new my_square(x,y,z,generateSize(),0),generateLifespan(),directionVector);
		particles->push_back(p);
	}
}

void my_emitter::update(float deltaTime) {
	std::vector<my_particle*> vec = *particles;

	//variable to check if we're ready for a new explosion
	bool anyOneAlive = false;

	//go through the particles and update them
	for(int i = 0; i < noOfParticles; i++) {
		vec[i]->update(deltaTime);

		//we want synchronised explosions, so check to make sure all particles are dead before generating a new one
		if(vec[i]->isDead() == false) {
			anyOneAlive = true;
		}
	}

	//generate new explosion
	if (anyOneAlive == false) {
		resetParticles(vec);
	}
}

void my_emitter::draw() {
	//call the draw function of all particles
	std::vector<my_particle*> vec = *particles;
	for(int i =0; i < noOfParticles; i++) {
		vec[i]->draw();
	}
}

my_emitter::~my_emitter(void)
{
	delete particles;
}

float my_emitter::generateMagnitude() {
	return rand() % 1000;
}

float my_emitter::generateLifespan() {
	return rand() % 100 + 1000;
}

float my_emitter::generateSize() {
	return (((float)rand() / (RAND_MAX)) + 1) * 2;
}

void my_emitter::resetParticles(std::vector<my_particle*> vec) {
	for (int i = 0; i < noOfParticles; i++) {
		//come up with new magnitude
		float magnitude = generateMagnitude();
		//reset the particle to the start position, and give it a new speed to go at
		vec[i]->reset(x, y, z, magnitude);
	}
}