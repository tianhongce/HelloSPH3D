#pragma once
#include "Vector3.h"
class Particle
{
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	Vector3 pressureForce;
	Vector3 gravityForce;
	Vector3 viscosityForce;
	Vector3 surfaceForce;

	float density;

	float mass;

public:
	Particle();
	~Particle();
};

