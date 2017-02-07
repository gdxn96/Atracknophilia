#pragma once
class Vector
{
public:
	Vector();
	Vector(int pX, int pY);
	~Vector();

	// member variables
	int x;
	int y;

	// operator functions
	Vector operator+(Vector pVector);
	Vector operator-(Vector pVector);
	Vector operator*(double pScalar);
	Vector operator/(double pScalar);

	Vector normalise();
	double dotProduct(Vector p_v, Vector p_b);
};

