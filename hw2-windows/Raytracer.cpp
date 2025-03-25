#include "Raytracer.h"
#include <iostream>

using namespace std;

Raytracer::Raytracer()
{
}

Intersection Raytracer::findIntersection(Ray r, Readfile* rf)
{
    vec3 black = vec3(0, 0, 0);
    float min_dist = INT_MAX;
    Object* min_obj = NULL;
    Intersection min_int = Intersection();
    
    for (int i = 0;i < rf->objList.size();i++) {

        Object* obj = (rf->objList)[i];

        /*cout << obj->type <<"\n";
        cout << obj->transform[0][0] << obj->transform[1][0] << obj->transform[2][0] << obj->transform[3][0] << "\n";
        cout << obj->transform[0][1] << obj->transform[1][1] << obj->transform[2][1] << obj->transform[3][1] << "\n";
        cout << obj->transform[0][2] << obj->transform[1][2] << obj->transform[2][2] << obj->transform[3][2] << "\n";
        cout << obj->transform[0][3] << obj->transform[1][3] << obj->transform[2][3] << obj->transform[3][3] << "\n";
        cout << "\n";*/
        

        //cout << obj->type;

        Intersection it = obj->hitObj(r);

        //cout << it.isHit;

        if (it.isHit) {
            float dist = length(it.pos - r.pos);

            if (dist > 0.001f && dist < min_dist) {
                min_dist = dist;
                min_obj = obj;
                min_int = it;
            }
        }

    }

    if (min_obj != NULL) {
        return min_int;
    }
    

    /*if (min_obj != NULL) {
        vec3 red = vec3(255, 0, 0);
        vec3 blue = vec3(0, 0, 255);

        if (min_obj->type == "triangle") {
            return red;
        }
        else if (min_obj->type == "sphere") {
            return blue;
        }
        return red;
    }*/


    return Intersection();
}

vec3 Raytracer::findColor(Ray r, Readfile* rf, int currDepth)
{
  
    vec3 color = vec3(0, 0, 0);

    Intersection hit = Raytracer::findIntersection(r, rf);

    if (hit.obj == NULL || currDepth > rf->maxDepth) {
        return color;
    }

    color = (hit.obj->ambient) + (hit.obj->emission);

    for (int i = 0; i < rf->lightList.size(); i++) {
        Lighting* currLight = (rf->lightList)[i];

        if (currLight->type == "point") {
            vec3 biased_pos = currLight->posOrDir + (hit.pos - currLight->posOrDir) * 0.001f;

            Ray lightRay = Ray(biased_pos, hit.pos - currLight->posOrDir);

            Intersection lightHit = Raytracer::findIntersection(lightRay, rf);

            if (lightHit.obj != NULL) {
                float intDist = glm::distance(hit.pos, lightHit.pos); 
                float distToLight = glm::distance(hit.pos, currLight->posOrDir);
                float distToObj = glm::distance(hit.pos, r.pos);
                
                if (intDist < 0.001f) {
                    
                    vec3 dir = glm::normalize(currLight->posOrDir - hit.pos);
                    vec3 col = currLight->color;
                    vec3 norm = hit.norm;
                    vec3 halfvec = glm::normalize(dir - glm::normalize(hit.pos - r.pos));
                    vec3 newColor = Raytracer::ComputeLight(dir, col, norm, halfvec, hit.obj->diffuse, hit.obj->specular, hit.obj->shininess);
                    color = color + newColor;

                    float r = distToLight;
                    color = color * (1.0f / (rf->attenuation[2] * r * r + rf->attenuation[1] * r + rf->attenuation[0]));
                    //color = vec3(0, 1, 0);

                }
            }

        } else { //directional produces black
            vec3 biased_pos = hit.pos + currLight->posOrDir * 0.001f;
            Ray lightRay = Ray(biased_pos, -currLight->posOrDir);

            Intersection lightHit = Raytracer::findIntersection(lightRay, rf);

            if (lightHit.obj == NULL) {
                vec3 dir = glm::normalize(currLight->posOrDir);
                vec3 col = currLight->color;
                vec3 norm = hit.norm;
                vec3 halfvec = glm::normalize(dir - glm::normalize(hit.pos - r.pos));

                color = color + Raytracer::ComputeLight(dir, col, norm, halfvec, hit.obj->diffuse, hit.obj->specular, hit.obj->shininess);
                //color = vec3(1, 0, 0);
            }
        }
    }
        //color = color * hit.obj->specular * Raytracer::findReflectionColor(hit, r, rf, rf->maxDepth);
        if (hit.obj->specular != vec3(0, 0, 0)) {
            // r ref = r incident - (2 * n * (r incident dot n))
            vec3 r_ref_dir = glm::normalize(r.dir) - ((glm::dot(glm::normalize(r.dir), hit.norm) * 2 * hit.norm));
            vec3 hit_pos = vec3(hit.pos[0], hit.pos[1], hit.pos[2]);
            Ray r_ref = Ray(hit_pos+hit.norm*0.001f, glm::normalize(r_ref_dir));
            Intersection it = Raytracer::findIntersection(r_ref, rf);

            if (it.obj != NULL) {   
                if (it.obj->type == "triangle" && currDepth > 1) {
                    //cout << it.obj->type << "\n";
                }
                
                color = color + hit.obj->specular * Raytracer::findColor(r_ref, rf, currDepth + 1);
            }
            //color = color + hit.obj->specular * raytracer::findcolor(hit, r_ref, rf, currdepth + 1);
 
        }
        
        //color[0] = color[0] * 255;
        //color[1] = color[1] * 255;
        //color[2] = color[2] * 255;
        
        /*vec3 red = vec3(255, 0, 0);
        vec3 blue = vec3(0, 0, 255);

        if (hit.obj->type == "triangle") {
            return red;
        }
        else if (hit.obj->type == "sphere") {
            return blue;
        }
        return red;*/

    if (color[0] > 1.0) {
        color[0] = 1.0;
    }
    if (color[1] > 1.0) {
        color[1] = 1.0;
    }
    if (color[2] > 1.0) {
        color[2] = 1.0;
    }

    return color;
}


//from hw 0
vec3 Raytracer::ComputeLight(vec3 direction, vec3 lightcolor, vec3 normal, vec3 halfvec, vec3 mydiffuse, vec3 myspecular, float myshininess) {

    
    float nDotL = std::max(dot(normal, direction), 0.0f);
    vec3 lambert = mydiffuse * lightcolor * (nDotL);

    float nDotH = std::max(dot(normal, halfvec), 0.0f);
    vec3 phong = myspecular * lightcolor * pow((nDotH), myshininess);

    vec3 res = lambert + phong;

    return res;
}

vec3 Raytracer::findReflectionColor(Intersection hit, Ray r, Readfile* rf, int depth)
{
    vec3 color = vec3(0, 0, 0);
    for (int i = 1; i <= depth; i++) {
        vec3 r_ref_dir = r.dir - ((glm::dot(r.dir, hit.norm) * 2 * hit.norm));
        Ray r_ref = Ray(hit.pos, glm::normalize(r_ref_dir));
        Intersection it = Raytracer::findIntersection(r_ref, rf);
        if (it.obj != NULL) {
            color = color + it.obj->specular * Raytracer::findColor(r_ref, rf, i);
        }
        
    }

    return color;
}





