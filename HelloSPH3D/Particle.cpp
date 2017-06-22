#include "Particle.h"


Particle::Particle()
{
	Vector3 O(0.0f, 0.0f, 0.0f);
	this->position;
	this->velocity;
	this->acceleration;

	this->pressureForce;
	this->gravityForce;
	this->viscosityForce;
	this->surfaceForce;

	this->density;
	this->mass;
}

Particle::Particle(Vector3 position)
{
	Vector3 O(0.0f, 0.0f, 0.0f);
	Vector3 Gravity(0.0f, -10.0f, 0.0f);
	this->position = position;
	this->velocity = O;
	this->acceleration = O;
	this->pressure = 0.0f;
	this->pressureForce = O;
	
	this->viscosityForce = O;
	this->surfaceForce = O;

	this->density = 1.0f;
	this->mass = 0.125f;

	this->gravityForce = Gravity*this->mass;
}


Particle::~Particle()
{
}
