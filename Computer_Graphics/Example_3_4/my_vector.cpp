#include "stdafx.h"
#include "my_vector.h"


my_vector::my_vector(float newX,float newY,float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}


my_vector::~my_vector(void)
{
}

bool my_vector::operator==(my_vector rhs) {
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

my_vector my_vector::operator-(my_vector rhs) {
	return my_vector(x - rhs.x, y - rhs.y, z - rhs.z);
}

my_vector my_vector::operator+(my_vector rhs) {
	return my_vector(x + rhs.x, y + rhs.y, z + rhs.z);
}

my_vector my_vector::operator+(float scalar) {
	return my_vector(x + scalar, y + scalar, z + scalar);
}

my_vector my_vector::operator-(float scalar) {
	return my_vector(x - scalar, y - scalar, z - scalar);
}

my_vector my_vector::operator*(float scalar) {
	return my_vector(x*scalar, y*scalar, z*scalar);
}

my_vector my_vector::operator/(float scalar) {
	return my_vector(x/scalar, y/scalar, z/scalar);
}

my_vector my_vector::crossProduct(my_vector rhs) {
	return my_vector(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}

float my_vector::dotProduct(my_vector rhs) {
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

float my_vector::length() {
	return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

void my_vector::normalise() {
	float len = length();
	x = x/len;
	y = y/len;
	z = z/len;
}