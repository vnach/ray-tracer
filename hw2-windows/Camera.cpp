#include "Camera.h"
#include "Readfile.h"


Camera::Camera()
{
}

Camera::Camera(vec3 from, vec3 at, vec3 u, float fovY, int width, int height)
{
    lookFrom = from;
    lookAt = at;
    up = u;
    fovy = (fovY * 3.1415f) / 180.0f;
    float tanfy = tanf(fovy / 2);
    wi = (float)width;
    ht = (float)height;

    fovx = 2.0f * atanf((tanfy * width) / height);
}

Camera::~Camera()
{
    lookFrom = vec3(0, 0, 0);
    lookAt = vec3(0, 0, 0);
    up = vec3(0, 0, 0);
    fovy = 0;
    fovx = 0;
}

Ray Camera::createRay(int x, int y)
{

    //discussion #9 - generate rays from camera

    //look at method
    vec3 w = glm::normalize(lookFrom - lookAt); //0 0 1
    vec3 u = glm::normalize(glm::cross(up, w)); // 1 0 0 
    vec3 v = glm::normalize(glm::cross(w, u)); // 0 1 0

    vec3 position = lookFrom;

    float alpha = tanf(fovx / 2.0f) * ((((float)x+0.50f) - ( wi/ 2.0f)) / (wi / 2.0f)); //-1.999906s
    float beta = tanf(fovy / 2.0f) * ((ht / 2.0f) - ((float)y-0.50f)) / (ht / 2.0f); //0.99990
    
    vec3 direction = (alpha * (u)) + (beta * (v)) - w; //(-1.99, 0.99, -1)
    direction = glm::normalize(direction); //(-0.816, 0.406, -0.410)
    return Ray(position, direction); // (0, 0, 1) __ dir as above
}
