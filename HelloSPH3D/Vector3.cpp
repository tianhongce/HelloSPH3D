#include "Vector3.h"


Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator + (Vector3 a)
{
	return Vector3(this->x + a.z, this->y + a.y, this->z + a.z);
}
Vector3 Vector3::operator - (Vector3 a)
{
	return Vector3(this->x - a.x, this->y - a.y, this->z - a.z);
}
Vector3 Vector3::operator / (float n)
{
	return Vector3(this->x / n, this->y / n, this->z / n);
}
Vector3 Vector3::operator * (float n)
{
	return Vector3(this->x * n, this->y * n, this->z * n);
}

ostream &operator<<(ostream &out, Vector3 a)
{
	out << "(" << a.x << ", " << a.y << ", " << a.z << ")" << endl;
	return out;
}

float dist(Vector3 a, Vector3 b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}