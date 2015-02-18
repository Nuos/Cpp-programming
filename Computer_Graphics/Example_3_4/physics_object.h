#pragma once
#include "my_vector.h"
#include "my_drawable.h"

class physics_object
{
public:
	float BOUNCE_FACTOR;
	float ENERGY_LOSS;
	float MAX_VELOCITY;

	my_vector displacement;

	physics_object(float,my_drawable*);
	~physics_object(void);

	void advance(float);
	void draw();
	void bounce(int,int,int);

	void applyImpulse(float,float,float);
	void applyForce(float,float,float);

	void disableGravity();
	void enableGravity();

	void rotate2D(my_vector);

	inline my_vector getVelocity() { return velocity; }
	inline void setEnergyLoss(float newVal) { ENERGY_LOSS = newVal; }
	inline void setMaxVelocity(float newVal) { MAX_VELOCITY = newVal; }
	inline void setDisplacement(my_vector newVal) { displacement = newVal; obj->x = newVal.x; obj->y = newVal.y; obj->z = newVal.z; }
private:
	my_vector velocity,gravity,directional_force;
	float mass;

	my_drawable* obj;
};

