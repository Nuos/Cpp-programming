#include "StdAfx.h"
#include "my_particle.h"


my_particle::my_particle(my_drawable* shape, int life, my_vector* dir)
{
	obj = new physics_object(0.5,shape);
	lifespan = life;
	lifespanMax = life;
	direction = dir;
	obj->applyForce(direction->x,direction->y,direction->z);
}


my_particle::~my_particle(void)
{
	delete obj;
}

void my_particle::update(float deltaTime) {
	obj->advance(deltaTime);
	lifespan--;
}

void my_particle::draw() {
	glPushMatrix();
		glColor4ub( 255, lifespan, 0, lifespan);
		obj->draw();
	glPopMatrix();
}

void my_particle::reset(float x, float y, float z, float magnitude) {
	obj->displacement.x = x;
	obj->displacement.y = y;
	obj->displacement.z = z;
	lifespan = lifespanMax;
	//reset velocity
	obj->applyImpulse(0,0,0);
	//apply the directional force
	direction->normalise();
	*direction = *direction * magnitude;
	obj->applyForce(direction->x,direction->y,direction->z);
}