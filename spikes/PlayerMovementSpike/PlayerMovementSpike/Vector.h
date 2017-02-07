#pragma once
class Vector
{
public:
	Vector();
	Vector(double pX, double pY);
	~Vector();

	// member variables
	double x;
	double y;

	// operator functions
	Vector operator+(Vector pVector);
	Vector operator-(Vector pVector);
	Vector operator*(double pScalar);
	Vector operator/(double pScalar);

	Vector normalise();
	double dotProduct(Vector p_v, Vector p_b);
};

