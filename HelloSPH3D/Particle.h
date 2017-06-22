#pragma once
#include "Vector3.h"
class Particle
{
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float pressure;
	Vector3 pressureForce;
	Vector3 gravityForce;
	Vector3 viscosityForce;
	Vector3 surfaceForce;

	Vector3 totalForce;

	float density;
	float mass;

public:
	Particle();
	Particle(Vector3 position);
	~Particle();
};

