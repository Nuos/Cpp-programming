#pragma once
class my_vector
{
public:
	inline my_vector() { };
	my_vector(float,float,float);
	~my_vector(void);

	bool operator==(my_vector rhs);
	my_vector operator-(my_vector rhs);
	my_vector operator+(my_vector rhs);
	my_vector operator+(float scalar);
	my_vector operator-(float scalar);
	my_vector operator*(float scalar);
	my_vector operator/(float scalar);
	my_vector crossProduct(my_vector rhs);
	float dotProduct(my_vector rhs);
	float length();
	void normalise();

	float x,y,z;
};

