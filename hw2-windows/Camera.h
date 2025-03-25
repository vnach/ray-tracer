#pragma once
#include "Ray.h"
using namespace glm;

class Camera
{

public:
	vec3 lookFrom;
	vec3 lookAt;
	vec3 up;
	float fovy;
	float fovx;
	float wi;
	float ht;

	Camera();

	Camera(vec3 from, vec3 at, vec3 u, float fovY, int width, int height);

	virtual ~Camera();

	Ray createRay(int x, int y);
	
};

