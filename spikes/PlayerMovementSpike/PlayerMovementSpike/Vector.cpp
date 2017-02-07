#include "stdafx.h"
#include "Vector.h"
#include <cmath>

Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(int pX, int pY)
{
	x = pX;
	y = pY;
}

Vector::~Vector()
{
}

Vector Vector::operator+(Vector pVector)
{
	return Vector(x + pVector.x, y + pVector.y);
}

Vector Vector::operator-(Vector pVector)
{
	return Vector(x - pVector.x, y - pVector.y);
}

Vector Vector::operator*(double pScalar)
{
	return Vector(x * pScalar, y * pScalar);
}

Vector Vector::operator/(double pScalar)
{
	return Vector(x / pScalar, y / pScalar);
}

Vector Vector::normalise()
{
	double magnitude = sqrt(x * x + y * y);
	return Vector(x / magnitude, y / magnitude);
}

double Vector::dotProduct(Vector p_v, Vector p_b)
{
	return (p_v.x * p_b.x + p_v.y * p_b.y);
}
