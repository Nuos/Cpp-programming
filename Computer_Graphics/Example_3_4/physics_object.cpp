#include "StdAfx.h"
#include "physics_object.h"


physics_object::physics_object(float newMass, my_drawable* shape)
{
	displacement = my_vector(shape->x,shape->y,shape->z);
	velocity = my_vector(0,0,0);
	gravity = my_vector(0,-9.81,0);
	obj = shape;
	mass = newMass;
}


physics_object::~physics_object(void)
{
	delete obj;
}

void physics_object::advance(float deltaTime) {
	my_vector acceleration = gravity;

	printf("Velocity: %f, Displacement: %f, deltaTime: %f, acceleration: %f\n",velocity.y,displacement.y,deltaTime,acceleration.y);

	displacement = displacement + velocity*deltaTime + acceleration*pow(deltaTime,2)*0.5;

	velocity = velocity + acceleration*deltaTime;

	obj->x = displacement.x;
	obj->y = displacement.y;
	obj->z = displacement.z;
}

void physics_object::draw() {
	obj->draw();
}

void physics_object::bounce(int xAxis, int yAxis, int zAxis) {
	velocity.x = velocity.x*xAxis;
	velocity.y = velocity.y*yAxis;
	velocity.z = velocity.z*zAxis;
}