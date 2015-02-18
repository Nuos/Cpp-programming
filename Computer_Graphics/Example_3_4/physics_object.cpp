#include "StdAfx.h"
#include "physics_object.h"


physics_object::physics_object(float newMass, my_drawable* shape)
{
	//Constants for a physics object
	BOUNCE_FACTOR = 0.7;
	//the amount of directional force kept at each simulation step
	ENERGY_LOSS = 0.9;
	//no upper bound on velocity and force by default
	MAX_VELOCITY = -1;

	//instantiate the relevant vectors
	displacement = my_vector(shape->x,shape->y,shape->z);
	velocity = my_vector(0,0,0);
	directional_force = my_vector(0,0,0);
	gravity = my_vector(0,-9.81,0);

	//attach a shape to the physical object
	obj = shape;
	mass = newMass;
}


physics_object::~physics_object(void)
{
	delete obj;
}

void physics_object::advance(float deltaTime) {

	//calculate the directional force remaining in this step
	directional_force = directional_force*ENERGY_LOSS;

	//a = f/m + acceleration due to gravity
	my_vector acceleration = directional_force/mass + gravity;

	//printf("Velocity: %f, Force: %f, deltaTime: %f, acceleration: %f\n",velocity.length(),directional_force.length(),deltaTime,acceleration.length());

	//calculate new values for velocity/displacement in this step
	velocity = velocity + acceleration*deltaTime;
	displacement = displacement + velocity*deltaTime;
	//displacement = displacement + velocity*deltaTime + acceleration*pow(deltaTime,2)*0.5;

	//coordinate max velocity if defined
	if (MAX_VELOCITY != -1) {
		if (velocity.length() > MAX_VELOCITY) {
			velocity = velocity.normalise()*MAX_VELOCITY;
		}
	}
	//apply the values to the underlying shape
	obj->x = displacement.x;
	obj->y = displacement.y;
	obj->z = displacement.z;
}

void physics_object::draw() {
	obj->draw();
}

void physics_object::bounce(int xAxis, int yAxis, int zAxis) {
	//bounce in the specified direction with a energy loss penalty
	velocity.x = velocity.x*xAxis*BOUNCE_FACTOR;
	velocity.y = velocity.y*yAxis*BOUNCE_FACTOR;
	velocity.z = velocity.z*zAxis*BOUNCE_FACTOR;
}

void physics_object::applyForce(float xdir, float ydir, float zdir) {
	//apply a force in a direction
	directional_force.x += xdir;
	directional_force.y += ydir;
	directional_force.z += zdir;
}

void physics_object::applyImpulse(float newX,float newY, float newZ) {
	//apply a sudden impulse in a specified direction
	velocity.x = newX;
	velocity.y = newY;
	velocity.z = newZ;
}

void physics_object::disableGravity() {
	//disable the gravity, useful for boids
	gravity = my_vector(0,0,0);
}

void physics_object::enableGravity() {
	//enable gravity
	gravity = my_vector(0,-9.81,0);
}

void physics_object::rotate2D(my_vector vec) {
	my_vector vecNorm = vec.normalise();
	float rotation = atan2(vecNorm.y,vecNorm.x)* 180.0 /M_PI - 90;
	//printf("Rotation: %f, x: %f, y: %f \n", rotation, vecNorm.x, vecNorm.y);
	obj->theta = rotation;
}