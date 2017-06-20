#include "Vector3.h"
#include <iostream>

using namespace std;

int main111()
{
	Vector3 a(0.0f, 0.0f, 0.0f);
	Vector3 b(1.0f, 0.0f, 3.0f);
	dist(a, b);
	//cout << dist(a, b) << endl;
	Vector3 c(1.0f, 2.0f, 6.0f);
	c = a * 0.6f;
	//cout << c << endl;
	Vector3 d = c - b;
	cout << a - d << endl;
	cout << b-c << endl;
	return 0;
}