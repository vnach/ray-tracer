// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
    mat3 ret;
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1.  
    float rad = glm::radians(degrees);

    vec3 a = glm::normalize(axis);
    mat3 identity = glm::mat3(1.0f);
    mat3 A = mat3(0, a[2], -a[1], -a[2], 0, a[0], a[1], -a[0], 0);
    mat3 aaT = mat3(a[0] * a[0], a[0] * a[1], a[0] * a[2], a[0] * a[1], a[1] * a[1], a[1] * a[2], a[0] * a[2], a[1] * a[2], a[2] * a[2]);

    ret = (cos(rad) * identity + (1 - cos(rad)) * (aaT)+(A * sinf(rad)));

    return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    mat3 rotMat = Transform::rotate(degrees, up);
    eye = rotMat * eye;

    printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.  

    vec3 axis = glm::cross(eye, up);
    mat3 rotMat = Transform::rotate(degrees, axis);

    eye = rotMat * eye;
    up = rotMat * up;

    printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

mat4 Transform::lookAt(const vec3& eye, const vec3& center, const vec3& up)
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.

    //vec3 center = vec3(0, 0, 0);

    vec3 w = glm::normalize(eye - center);
    vec3 u = glm::normalize(glm::cross(up, w));
    vec3 v = (glm::cross(w, u));


    mat4 Ruvw = mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
    mat4 transE = glm::mat4(1.0f);
    vec3 neye = glm::normalize(eye);
    transE[3][0] = -1 * eye.x;
    transE[3][1] = -1 * eye.y;
    transE[3][2] = -1 * eye.z;

    ret = Ruvw * transE;

    return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.  

    float t = glm::radians(fovy) / 2;
    ret = mat4(1 / (aspect * tan(t)), 0, 0, 0,
        0, 1 / (tan(t)), 0, 0,
        0, 0, -(zFar + zNear) / (zFar - zNear), -1,
        0, 0, -(2 * zFar * zNear) / (zFar - zNear), 0);



    return ret;
}

mat4 Transform::scale(const float& sx, const float& sy, const float& sz)
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 
    ret = glm::mat4(1.0f);
    ret[0][0] = sx;
    ret[1][1] = sy;
    ret[2][2] = sz;

    return ret;
}

mat4 Transform::translate(const float& tx, const float& ty, const float& tz)
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
    ret = glm::mat4(1.0f);
    ret[3][0] = tx;
    ret[3][1] = ty;
    ret[3][2] = tz;
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3& up, const vec3& zvec)
{
    vec3 x = glm::cross(up, zvec);
    vec3 y = glm::cross(zvec, x);
    vec3 ret = glm::normalize(y);
    return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
