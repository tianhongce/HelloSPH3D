#include "SPH.h"


SPH::SPH()
{
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
	Vector3 w = (O-Vr)*(45 / (M_PI*r*(pow(kernel, 9))))*(kernel - r)*(kernel - r);
	return w;
}
float SPH::cal_w_visco_ss_value(Vector3 a, Vector3 b)
{
	float r = dist(a, b);
	float w = 45 * (kernel - r) / (M_PI*(pow(kernel, 6)));
	return w;
}
void SPH::addParticles()
{

}
void SPH::calDensity()
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
					float w = cal_w_poly6_value(particles[i]->position, particles[j]->position);

					//float r = dist(particles[i]->position, particles[j]->position);
					//float w = pow(kernel*kernel - r*r, 3) * 315 / (64 * M_PI*(pow(kernel, 9)));
					particles[i]->density = particles[i]->density + w;
				}
				
			}
		}

	}
}
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
					float K = 1.0f;
					float pi = K*(particles[i]->density - restDensity);
					float pj = K*(particles[j]->density - restDensity);

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

					float u;

					Vector3 tempviscosityForce = (particles[j]->velocity - particles[i]->velocity)*particles[j]->mass / particles[j]->density*u*w;

					particles[i]->viscosityForce = particles[i]->viscosityForce + tempviscosityForce;

				}

			}
		}

	}
}
void SPH::calTotalForce()
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
					//计算压力
					float K = 1.0f;
					float pi = K*(particles[i]->density - restDensity);
					float pj = K*(particles[j]->density - restDensity);

					Vector3 w_pressure = cal_w_spiky_s_value(particles[i]->position, particles[j]->position);
					Vector3 O(0.0f, 0.0f, 0.0f);
					Vector3 tempPressureForce = O - (w_pressure * particles[j]->mass*(pi + pj) / (2 * particles[j]->density));
					particles[i]->pressureForce = particles[i]->pressureForce + tempPressureForce;

					//计算粘度力
					float w = cal_w_visco_ss_value(particles[i]->position, particles[j]->position);
					float u;
					Vector3 tempviscosityForce = (particles[j]->velocity - particles[i]->velocity)*particles[j]->mass / particles[j]->density*u*w;
					particles[i]->viscosityForce = particles[i]->viscosityForce + tempviscosityForce;

					
				}

			}
		}

		//计算合力
		Vector3 totalForce = particles[i]->pressureForce + particles[i]->viscosityForce;
		//计算加速度
		particles[i]->acceleration = totalForce / particles[i]->density;
		
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
			particles[i]->velocity.x = -particles[i]->velocity.x;
			particles[i]->position.x = min_x_boundary;
		}
		if (particles[i]->position.y < min_y_boundary)
		{
			particles[i]->velocity.y = -particles[i]->velocity.y;
			particles[i]->position.y = min_y_boundary;
		}
		if (particles[i]->position.z < min_z_boundary)
		{
			particles[i]->velocity.z = -particles[i]->velocity.z;
			particles[i]->position.z = min_z_boundary;
		}
		if (particles[i]->position.x > max_x_boundary)
		{
			particles[i]->velocity.x = -particles[i]->velocity.x;
			particles[i]->position.x = max_x_boundary;
		}
		if (particles[i]->position.y > max_y_boundary)
		{
			particles[i]->velocity.y = -particles[i]->velocity.y;
			particles[i]->position.y = max_y_boundary;
		}
		if (particles[i]->position.z > max_z_boundary)
		{
			particles[i]->velocity.z = -particles[i]->velocity.z;
			particles[i]->position.z = max_z_boundary;
		}
	}
	
}

void SPH::simulation()
{
	calDensity();
	calTotalForce();
}