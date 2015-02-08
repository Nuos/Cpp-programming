#include "StdAfx.h"
#include "physics_object.h"


physics_object::physics_object(float newMass, my_drawable* shape)
{
	BOUNCE_FACTOR = 0.7;
	ENERGY_LOSS = 0.9;

	displacement = my_vector(shape->x,shape->y,shape->z);
	velocity = my_vector(0,0,0);
	directional_force = my_vector(0,0,0);
	gravity = my_vector(0,-9.81,0);
	obj = shape;
	mass = newMass;
}


physics_object::~physics_object(void)
{
	delete obj;
}

void physics_object::advance(float deltaTime) {
	directional_force = directional_force*ENERGY_LOSS;
	my_vector acceleration = directional_force/mass + gravity;

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
	velocity.x = velocity.x*xAxis*BOUNCE_FACTOR;
	velocity.y = velocity.y*yAxis*BOUNCE_FACTOR;
	velocity.z = velocity.z*zAxis*BOUNCE_FACTOR;
}

void physics_object::applyForce(float xdir, float ydir, float zdir) {
	directional_force.x = xdir;
	directional_force.y = ydir;
	directional_force.z = zdir;
}

void physics_object::applyImpulse(float newX,float newY, float newZ) {
	velocity.x = newX;
	velocity.y = newY;
	velocity.z = newZ;
}