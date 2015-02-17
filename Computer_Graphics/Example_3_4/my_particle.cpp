#include "StdAfx.h"
#include "my_particle.h"


my_particle::my_particle(my_drawable* shape, float life, my_vector* dir)
{
	//create the particle for the shape specified
	obj = new physics_object(0.5,shape);
	lifespan = life;
	lifespanMax = life;
	direction = dir;
	//apply the directional force given
	obj->applyForce(direction->x,direction->y,direction->z);
}


my_particle::~my_particle(void)
{
	delete obj;
}

void my_particle::update(float deltaTime) {
	//advance the physics + decrement the lifespan
	obj->advance(deltaTime);
	if (lifespan > 0)
		lifespan--;
}

void my_particle::draw() {
	//printf("Lifespan percent: %f \n", lifespan / lifespanMax);
	glPushMatrix();
	//alter colour and alpha for dramatic effect
	glColor4ub(255, 255.0*(lifespan / lifespanMax*1.0), 0, 255.0*(lifespan / lifespanMax*1.0));
		obj->draw();
	glPopMatrix();
}

void my_particle::reset(float newX, float newY, float newZ, float magnitude) {
	//printf("Resetting particle!");

	//reset the position and lifespan
	obj->setDisplacement(my_vector(newX,newY,newZ));
	lifespan = lifespanMax;

	//reset velocity
	obj->applyImpulse(0,0,0);

	//apply the new directional force
	direction = direction->normalise();
	*direction = *direction * magnitude;
	obj->applyForce(direction->x,direction->y,direction->z);
}