#pragma once
#include "Particle.h"
#include <vector>
#include <math.h>
#define M_PI 3.14159265358979323846

class SPH
{
public:
	float kernel;
	float cal_w_poly6_value(Vector3 a, Vector3 b);
	Vector3 cal_w_spiky_s_value(Vector3 a, Vector3 b);
	float cal_w_visco_ss_value(Vector3 a, Vector3 b);

	vector<Particle*> particles;

	int numParticles;

	float restDensity;
	float t;
	float min_x_boundary;
	float max_x_boundary;
	float min_y_boundary;
	float max_y_boundary;
	float min_z_boundary;
	float max_z_boundary;
public:
	SPH();
	~SPH();

	void initFluid();
	vector<Particle*> getParticles();

	void addParticles();
	void calDensity();
	void calPressure();
	void calPressureForce();
	void calviscosityForce();
	void calTotalForce();
	void calPosition();

	void simulation();

};

