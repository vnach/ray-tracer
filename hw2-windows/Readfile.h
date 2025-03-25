#include <vector>
#include <stack>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Object.h"
#include "Lighting.h"
#include "Camera.h"
#include <string>
using namespace std;

class Readfile
{
	//necessary vars from .test file

	public:

		int width;
		int height;
		int maxDepth;
		string outputFile;
		float attenuation[3];
		Camera cam;

		//material properties
		vec3 ambient;
		vec3 diffuse;
		vec3 emission;
		vec3 specular;
		float shininess;

		//transform
		stack <mat4> t_stack;
		//transfstack.push(mat4(1.0));
		// identity

		vector<Object*> objList;
		int maxVerts;
		vector<vec3> triVerts;
		int maxNorms;
		vector<vec3> triNorms;
		vector<Lighting*> lightList;


		Readfile();
		virtual ~Readfile();

		void Readfile::readfile(const char* filename);

};

#pragma once
