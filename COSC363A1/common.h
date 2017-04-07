#pragma once

#include <GL/freeglut.h>
#include <cmath>
#include <cstring>
#include <iostream>

const double PI = 3.141592653589793238463f;

inline void setNormal(float v1[3], float v2[3], float v3[3])
{
	float n[3];
	n[0] = v1[1] * (v2[2] - v3[2]) + v2[1] * (v3[2] - v1[2]) + v3[1] * (v1[2] - v2[2]);
	n[1] = v1[2] * (v2[0] - v3[0]) + v2[2] * (v3[0] - v1[0]) + v3[2] * (v1[0] - v2[0]);
	n[2] = v1[0] * (v2[1] - v3[1]) + v2[0] * (v3[1] - v1[1]) + v3[0] * (v1[1] - v2[1]);
	glNormal3f(n[0], n[1], n[2]);
}

inline void getNormal(float v1[3], float v2[3], float v3[3], float out[3])
{
	out[0] = v1[1] * (v2[2] - v3[2]) + v2[1] * (v3[2] - v1[2]) + v3[1] * (v1[2] - v2[2]);
	out[1] = v1[2] * (v2[0] - v3[0]) + v2[2] * (v3[0] - v1[0]) + v3[2] * (v1[0] - v2[0]);
	out[2] = v1[0] * (v2[1] - v3[1]) + v2[0] * (v3[1] - v1[1]) + v3[0] * (v1[1] - v2[1]);
}