#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace glm;
using namespace std;

class Ray
{
public:
    vec3 pos;
    vec3 dir;
    Ray(vec3 position, vec3 direction) {
        pos = position;
        dir = direction;
    }

    Ray transform(const mat4 mat) {
        vec3 position;
        vec3 direction;
        vec4 transP = mat * vec4(pos, 1); // homogenous coord for pos
        vec4 transD = mat * vec4(dir, 0); // non homogenous coord for dir
        position = vec3(transP[0]/transP[3], transP[1]/transP[3], transP[2]/transP[3]);
        direction = vec3(transD);
        return Ray(position, glm::normalize(direction));
    }

    vec3 at(float t) {
        return pos + (t * dir);
    }


};


