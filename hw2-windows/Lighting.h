#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "Ray.h"


using namespace glm;

class Lighting
{
public:
	vec3 posOrDir;
	vec3 color;
	//enum type{directional, point};
	string type;

	Lighting(vec3 pOrd, vec3 col) {
		posOrDir = pOrd;
		color = col;
	}

};

