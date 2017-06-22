#include "SPH.h"


SPH::SPH()
{
	this->kernel = 0.25f;
	this->numParticles = 0;
	this->restDensity = 1000.0f;
	this->t = 0.001f;
	this->min_x_boundary = -0.5f;
	this->max_x_boundary = 0.5f;
	this->min_y_boundary = -0.5f;
	this->max_y_boundary = 0.5f;
	this->min_z_boundary = -0.5f;
	this->max_z_boundary = 0.5f;

	
}


SPH::~SPH()
{
}

float SPH::cal_w_poly6_value(Vector3 a, Vector3 b)
{

	float r = dist(a, b);
	float w = pow(kernel*kernel - r*r, 3) * 315 / (64 * M_PI*(pow(kernel, 9)));
	return w;
}
Vector3 SPH::cal_w_spiky_s_value(Vector3 a, Vector3 b)
{
	float r = dist(a, b);
	Vector3 Vr = a - b;
	Vector3 O(0.0f, 0.0f, 0.0f);
	Vector3 w = (O-Vr)*(45 / (M_PI*r*(pow(kernel, 6))))*(kernel - r)*(kernel - r);
	return w;
}
float SPH::cal_w_visco_ss_value(Vector3 a, Vector3 b)
{
	float r = dist(a, b);
	float w = 45 * (kernel - r) / (M_PI*(pow(kernel, 6)));
	return w;
}

void SPH::initFluid()
{
	addParticles();
}

void SPH::addParticles()
{
	for (float i = -0.4; i < 0.1; i = i+0.05f)
	{
		for (float j = -0.4; j < 0.3; j = j + 0.05f)
		{
			for (float k = -0.4; k < 0.1; k = k + 0.05f)
			{
				
				Vector3 pp(i, j, k);
				Particle *p = new Particle(pp);

				particles.push_back(p);
				numParticles++;
			}
		}
	}
}

vector<Particle*> SPH::getParticles()
{
	return this->particles;
}

void SPH::calDensity()
{
	//cout << numParticles << endl;
	for (int i = 0; i < numParticles; i++)
	{
		particles[i]->density = 0.0f;

		for (int j = 0; j < numParticles; j++)
		{
			//if (i != j)
			{
				float D = dist(particles[i]->position, particles[j]->position);

				if (D <= kernel&&D >= 0)
				{
					float w = cal_w_poly6_value(particles[i]->position, particles[j]->position);

					//float r = dist(particles[i]->position, particles[j]->position);
					//float w = pow(kernel*kernel - r*r, 3) * 315 / (64 * M_PI*(pow(kernel, 9)));
					particles[i]->density = particles[i]->density + particles[i]->mass * w;
				}
				
			}
		}

	}
}
/*--------------------------------------------------------------------------------------------------------------------
void SPH::calPressureForce()
{
	for (int i = 0; i < numParticles; i++)
	{
		for (int j = 0; j < numParticles; j++)
		{
			if (i != j)
			{
				float D = dist(particles[i]->position, particles[j]->position);

				if (D <= kernel&&D >= 0)
				{
					float K = 1200.0f;
					//float pi = K*(particles[i]->density - restDensity);
					//float pj = K*(particles[j]->density - restDensity);

					float pi = K*(pow(particles[i]->density / restDensity, 7) - 1);
					float pj = K*(pow(particles[j]->density / restDensity, 7) - 1);

					Vector3 w = cal_w_spiky_s_value(particles[i]->position, particles[j]->position);
					Vector3 O(0.0f, 0.0f, 0.0f);
					Vector3 tempPressureForce = O - (w * particles[j]->mass*(pi + pj) / (2 * particles[j]->density));

					particles[i]->pressureForce = particles[i]->pressureForce + tempPressureForce;

				}
				
			}
		}

	}
}

void SPH::calviscosityForce()
{
	for (int i = 0; i < numParticles; i++)
	{
		for (int j = 0; j < numParticles; j++)
		{
			if (i != j)
			{
				float D = dist(particles[i]->position, particles[j]->position);

				if (D <= kernel&&D >= 0)
				{
					float w = cal_w_visco_ss_value(particles[i]->position, particles[j]->position);

					float u = 1.0f;

					Vector3 tempviscosityForce = (particles[j]->velocity - particles[i]->velocity)*particles[j]->mass / particles[j]->density*u*w;

					particles[i]->viscosityForce = particles[i]->viscosityForce + tempviscosityForce;

				}

			}
		}

	}
}
--------------------------------------------------------------------------------------------------------------------------------------------------------*/
void SPH::calPressure()
{
	for (int i = 0; i < numParticles; i++)
	{
		float K = 0.01f;
		particles[i]->pressure = K / 7 * restDensity*(pow(particles[i]->density / restDensity, 7) - 1);
	}
}

void SPH::calTotalForce()
{
	Vector3 temp_force;

	for (int i = 0; i < numParticles; i++)
	{
		Vector3 O(0.0f, 0.0f, 0.0f);
		particles[i]->pressureForce = O;
		particles[i]->viscosityForce = O;

		for (int j = 0; j < numParticles; j++)
		{
			if (i != j)
			{
				float D = dist(particles[i]->position, particles[j]->position);

				if (D <= kernel&&D >= 0)
				{
					//计算压力,外部计算
					//float K = 1200.0f;
					//float pi = K*(particles[i]->density - restDensity);
					//float pj = K*(particles[j]->density - restDensity);
					//float pi = K*(pow(particles[i]->density / restDensity, 7) - 1);
					//float pj = K*(pow(particles[j]->density / restDensity, 7) - 1);

					Vector3 w1 = cal_w_spiky_s_value(particles[i]->position, particles[j]->position);
					
					//Vector3 tempPressureForce = O - (w1 * particles[j]->mass*(pi + pj) / (2 * particles[j]->density));
					Vector3 tempPressureForce = O - (w1 * particles[j]->mass*(particles[i]->pressure + particles[j]->pressure) / (2 * particles[j]->density));
					particles[i]->pressureForce = particles[i]->pressureForce + tempPressureForce;
					//cout << tempPressureForce << endl;
					//cout << particles[i]->pressureForce << endl;



					//此段用于试验加速度
					//temp_force =  tempPressureForce;
					//cout << temp_force << endl;
					//particles[i]->acceleration = temp_force;
					
					//计算粘度力
					float w2 = cal_w_visco_ss_value(particles[i]->position, particles[j]->position);
					float u = 0.0035f;
					Vector3 tempviscosityForce = ((particles[j]->velocity - particles[i]->velocity)*particles[j]->mass / particles[j]->density)*u*w2; 
					particles[i]->viscosityForce = particles[i]->viscosityForce + tempviscosityForce;

					//此段用于试验加速度
				    //temp_force = tempviscosityForce;
					//particles[i]->acceleration = temp_force;

					
				}

			}
		}

		//计算合力
		//cout << particles[i]->pressureForce << endl;
		Vector3 I(0.0f, -1.0f, 0.0f);
		particles[i]->gravityForce = I * particles[i]->mass*9.8;
		particles[i]->totalForce = particles[i]->pressureForce + particles[i]->viscosityForce + particles[i]->gravityForce;
		//计算加速度
		//particles[i]->acceleration = totalForce / particles[i]->density;
		particles[i]->acceleration = particles[i]->totalForce / particles[i]->mass;
		
	}

}

void SPH::calPosition()
{
	for (int i = 0; i < numParticles; i++)
	{
		//计算速度
		particles[i]->velocity = particles[i]->velocity + particles[i]->acceleration * t;

		//计算位置
		particles[i]->position = particles[i]->position + particles[i]->velocity * t;

		//边界限制条件

		if (particles[i]->position.x < min_x_boundary)
		{
			particles[i]->velocity.x = particles[i]->velocity.x*(-0.5f);
			particles[i]->position.x = min_x_boundary + 0.0001;
		}
		if (particles[i]->position.y < min_y_boundary)
		{
			particles[i]->velocity.y = particles[i]->velocity.y*(-0.5f);
			particles[i]->position.y = min_y_boundary + 0.0001;
		}
		if (particles[i]->position.z < min_z_boundary)
		{
			particles[i]->velocity.z = particles[i]->velocity.z*(-0.5f);
			particles[i]->position.z = min_z_boundary + 0.0001;
		}
		if (particles[i]->position.x > max_x_boundary)
		{
			particles[i]->velocity.x = particles[i]->velocity.x*(-0.5f);
			particles[i]->position.x = max_x_boundary - 0.0001;
		}
		if (particles[i]->position.y > max_y_boundary)
		{
			particles[i]->velocity.y = particles[i]->velocity.y*(-0.5f);
			particles[i]->position.y = max_y_boundary - 0.0001;
		}
		if (particles[i]->position.z > max_z_boundary)
		{
			particles[i]->velocity.z = particles[i]->velocity.z*(-0.5f);
			particles[i]->position.z = max_z_boundary-0.0001;
		}
	}
	int i = 0;
}

void SPH::simulation()
{
	calDensity();
	calPressure();
	calTotalForce();
	calPosition();
}
