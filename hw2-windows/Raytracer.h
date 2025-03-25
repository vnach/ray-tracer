#pragma once

#include "Ray.h";
#include "Readfile.h";
#include "Object.h";

class Raytracer
{

public:
	Raytracer();
	Intersection findIntersection(Ray r, Readfile* rf);
	vec3 findColor(Ray r, Readfile* rf, int currDepth);
	vec3 ComputeLight(vec3 direction, vec3 lightcolor, vec3 normal, vec3 halfvec, vec3 mydiffuse, vec3 myspecular, float myshininess);
	vec3 findReflectionColor(Intersection hit, Ray r, Readfile* rf, int newDepth);
	
};

