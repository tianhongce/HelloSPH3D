#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class Vector3
{
public:
	float x;
	float y;
	float z;
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	Vector3 operator + (Vector3 a);
	Vector3 operator - (Vector3 a);
	Vector3 operator * (float n);
	Vector3 operator / (float n);

	friend ostream &operator<<(ostream &out, Vector3 a);
	friend float dist(Vector3 a, Vector3 b);
};

