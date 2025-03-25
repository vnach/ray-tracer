#pragma once
#include "Ray.h"
#include <iostream>

using namespace std;


class Object;

class Intersection;

class Intersection {
    public:
    Object* obj;
    vec3 pos;
    vec3 norm;
    bool isHit;

    Intersection() {
        pos = vec3(0, 0, 0);
        norm = vec3(0, 0, 0);
        obj = NULL;
        isHit = false;
    }
    Intersection(vec3 position, vec3 normal, Object* object) {
        pos = position;
        norm = normal;
        obj = object;
        isHit = true;
    }
};

class Object {
public:
    mat4 transform;
    mat4 InversedTransform;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shininess;


    enum shape { triangle, sphere };
    string type;

    Object() {}

    virtual Intersection hitObj(Ray r) {
        //cout << "here";
        return Intersection();
    }
    vec3 hitNorm(vec3 vector) {
        return vec3(0, 0, 0);
    }

};

class Sphere : public Object {
public:
    vec3 origin;
    float rad;
    
    Sphere(vec3 o, float r) {
        type = sphere;
        origin = o;
        rad = r;
        ambient = vec3(0, 0, 0);
        emission = vec3(0, 0, 0);
        diffuse = vec3(0, 0, 0);
        specular = vec3(0, 0, 0);
        shininess = 0.0;
        transform = mat4(1.0);
        InversedTransform = glm::inverse(transform);
    }

    virtual ~Sphere() {};

    virtual Intersection hitObj(Ray ray) {

        //cout << "SPH \n";

        //return Intersection(ray.pos, vec3(0, 0, 0), this);
        Ray tr = ray.transform(InversedTransform);

        //quadratic formula
        vec3 p0 = tr.pos;
        vec3 p1 = tr.dir;
        vec3 center = this->origin;

        float a = glm::dot(p1, p1); //0.998
        float b = 2.0f * glm::dot(p1, p0-center); //-0.408
        float c = glm::dot(p0 - center, p0 - center) - (this->rad * this->rad); //0

        float disc = (b * b) - (4 * a * c); //0.66658


        float t0 = (-b + sqrt(disc)) / (2 * a); //0.816
        float t1 = (-b - sqrt(disc)) / (2 * a); //0
        
        float t = 0;
        if (disc < 0) {
            return Intersection();
        }
        if (t0 > -0.0001 && t1 > -0.0001) {
            if (t1 >= t0) {
                t = t0;
            }
            else {
                t = t1;
            }
        }
        else if (t0 > -0.0001) {
            t = t0;
        }
        else if (t1 > -0.0001) {
            t = t1;
        }
        else {
            return Intersection();
        }

        //std::cout << "t0 = " << t0;
        //std::cout << " t1 = " << t1;
        //std::cout << "\n" ;


        if (t == 0) {
            //return false;
            return Intersection(); //no intersection
        }
        else {
            vec4 transP = transform * vec4(tr.at(t), 1);
            vec3 newPosition = vec3(transP);
            vec3 norm = this->hitNorm(newPosition);
            //cout << " yes \n";
            //return true;
            return Intersection(newPosition, norm, this);


        }

    }


    vec3 hitNorm(const vec3 point) {
        vec4 transP = InversedTransform * vec4(point, 1);
        vec4 newVec = transP - vec4(this->origin, 0);
        vec4 newNorm = glm::transpose(InversedTransform) * newVec;
        vec3 normal = glm::normalize(vec3(newNorm));
        
        // norm = (M^-1)^T * norm

        return normal;
    }
};

class Triangle : public Object {
public:
    vec3 a, b, c;

    
    Triangle(vec3 a1, vec3 b1, vec3 c1) {
        type = triangle;

        a = a1;
        b = b1;
        c = c1;

        ambient = vec3(0, 0, 0);
        emission = vec3(0, 0, 0);
        diffuse = vec3(0, 0, 0);
        specular = vec3(0, 0, 0);
        shininess = 0.0;
        transform = mat4(1.0);
        InversedTransform = glm::inverse(transform);

    }
    virtual ~Triangle() {}

    void transformObject(mat4 trans) {
        vec4 transA = trans* vec4(a, 1);
        vec4 transB = trans * vec4(b, 1);
        vec4 transC = trans * vec4(c, 1);
        a = vec3(transA.x/transA.w, transA.y/transA.w, transA.z/transA.w);
        b = vec3(transB.x / transB.w, transB.y / transB.w, transB.z / transB.w);
        c = vec3(transC.x / transC.w, transC.y / transC.w, transC.z / transC.w);
    }

    virtual Intersection hitObj(Ray ray) {

        //cout << "TRI \n";

        Ray tr = ray.transform(InversedTransform);


        vec3 normal = glm::cross((b - a), (c - a));
        float t = (glm::dot(a, normal) - glm::dot(tr.pos, normal) )  / glm::dot(normal, tr.dir);
        if (t < 0) {
            return Intersection();
        }

        vec3 position = tr.pos + t * tr.dir;

        mat3 baryCent = mat3(this->a, this->b, this->c);

        vec3 coeff = (position) * glm::inverse(baryCent);
        float alpha = coeff[0];
        float beta = coeff[1];
        float gamma = coeff[2];

        vec3 edgeA = glm::cross((position - a), (a - b));
        vec3 edgeB = glm::cross((position - b), (b - c));
        vec3 edgeC = glm::cross((position - c), (c - a));

        if (glm::dot(edgeA, normal) > -0.0001 && glm::dot(edgeB, normal) > -0.0001 && glm::dot(edgeC, normal) > -0.0001)
        {
            vec4 transP = transform * vec4(tr.at(t), 1);
            vec3 newPosition = vec3(transP);
            vec3 norm = this->hitNorm(newPosition);
            //cout << " yes \n";
            //return true;
            return Intersection(newPosition, vec3(norm), this);
        }
        else {
            return Intersection();
        }

    }

    vec3 hitNorm(const vec3& point) {
         
        vec3 norm = glm::cross((b - a), (c - a)); //flip b/c gives normals in opposite direction
        vec4 newNorm = glm::transpose(InversedTransform) * vec4(norm, 0);
        return glm::normalize(vec3(newNorm)); 
    }
};



