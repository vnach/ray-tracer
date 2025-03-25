/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix 
// transformations for a stack (matransform) and to rightmultiply the 
// top of a stack.  These functions are given to aid in setting up the 
// transformations properly, and to use glm functions in the right way.  
// Their use is optional in your program.  


// The functions readvals and readfile do basic parsing.  You can of course 
// rewrite the parser as you wish, but we think this basic form might be 
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE. 
// Read the other parts to get a context of what is going on. 

/*****************************************************************************/

// Basic includes to get this file to work.  
 

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Transform.h" 
#include "Object.h"
#include "Lighting.h"

using namespace std;
//#include "variables.h" 
#include "Readfile.h"

// You may not need to use the following two functions, but it is provided
// here for convenience

// The function below applies the appropriate transform to a 4-vector
void matransform(stack<mat4>& transfstack, GLfloat* values)
{
    mat4 transform = transfstack.top();
    vec4 valvec = vec4(values[0], values[1], values[2], values[3]);
    vec4 newval = transform * valvec;
    for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void rightmultiply(const mat4& M, stack<mat4>& transfstack)
{
    mat4& T = transfstack.top();
    T = T * M;
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream& s, const int numvals, GLfloat* values)
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

void Readfile::readfile(const char* filename)
{
    vec3 ambient = vec3(0, 0, 0);
    vec3 emission = vec3(0, 0, 0);
    vec3 diffuse = vec3(0, 0, 0);
    vec3 specular = vec3(0, 0, 0);
    float shininess = 0.0f;
    stack<mat4> t_stack;
    t_stack.push(mat4(1.0f));

    string str, cmd;
    ifstream in;
    in.open(filename);
    if (in.is_open()) {

        // I need to implement a matrix stack to store transforms.  
        // This is done using standard STL Templates 
        //stack <mat4> transfstack;
        //transfstack.push(mat4(1.0));  // identity

        getline(in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines 

                stringstream s(str);
                s >> cmd;
                int i;
                GLfloat values[10]; // Position and color for light, colors for others
                // Up to 10 params for cameras.  
                bool validinput; // Validity of input 

                if (cmd == "output") {
                    s >> outputFile;
                }
                // Process the light, add it to database.
                // Lighting Command
                
                else if (cmd == "directional") {
                    validinput = readvals(s, 6, values);
                    if (validinput) {
                        vec3 dir = vec3(values[0], values[1], values[2]);
                        vec3 color = vec3(values[3], values[4], values[5]);

                        Lighting* light = new Lighting(dir, color);
                        light->type = "directional";
                        this->lightList.push_back(light);
                    }
                }

                else if (cmd == "point") {
                    validinput = readvals(s, 6, values);
                    if (validinput) {
                        vec3 pos = vec3(values[0], values[1], values[2]);
                        vec3 color = vec3(values[3], values[4], values[5]);

                        Lighting* light = new Lighting(pos, color);
                        light->type = "point";
                        this->lightList.push_back(light);
                    }
                }
            
                
                
                
            
                // Material Commands 
                // Ambient, diffuse, specular, shininess properties for each object.
                // Filling this in is pretty straightforward, so I've left it in 
                // the skeleton, also as a hint of how to do the more complex ones.
                // Note that no transforms/stacks are applied to the colors. 

                else if (cmd == "attenuation") {
                    validinput = readvals(s, 3, values); // colors 
                    if (validinput) {
                        this->attenuation[0] = values[0];
                        this->attenuation[1] = values[1];
                        this->attenuation[2] = values[2];
                    }
                }
                
                else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors 
                    if (validinput) {
                        ambient = vec3(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        diffuse = vec3(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "specular") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        specular = vec3(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "emission") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        emission = vec3(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        shininess = values[0];
                    }
                }
                

                else if (cmd == "size") {
                    validinput = readvals(s, 2, values);
                    if (validinput) {
                        width = (int)values[0];
                        height = (int)values[1];

                        
                    }
                }

                else if (cmd == "maxdepth") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        maxDepth = values[0];


                    }
                }

                else if (cmd == "camera") {
                    validinput = readvals(s, 10, values); // 10 values eye cen up fov
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE
                        // Use all of values[0...9]
                        // You may need to use the upvector fn in Transform.cpp
                        // to set up correctly. 
                        // Set eyeinit upinit center fovy in variables.h 
                 
                        vec3 lookFrom = (vec3(values[0], values[1], values[2]));
                        vec3 lookAt = (vec3(values[3], values[4], values[5]));
                        vec3 up = (vec3(values[6], values[7], values[8]));

                        float fovy = values[9];

                        cam = Camera(lookFrom, lookAt, up, fovy, width, height);
                        
                    }
                }

                // I've left the code for loading objects in the skeleton, so 
                // you can get a sense of how this works.  
                // Also look at demo.txt to get a sense of why things are done this way.
 
                else if (cmd == "sphere") {
                    validinput = readvals(s, 4, values);
                    if (validinput) {
                        Sphere* obj = new Sphere(vec3(values[0], values[1], values[2]), values[3]);

                        
                        // Set the object's light properties
                     
                        obj->ambient = ambient;
                        obj->emission = emission;
                        obj->diffuse = diffuse;
                        obj->specular = specular;
                        obj->shininess = shininess;
                        obj->type = "sphere";

                        // Set the object's transform
                        obj->transform = t_stack.top();
                        obj->InversedTransform = glm::inverse(t_stack.top());
                        this->objList.push_back(obj);
                       
                    }
                    
                }

                else if (cmd == "maxverts") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        maxVerts = values[0];
                    }

                }
                else if (cmd == "maxvertnorms") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        maxNorms = values[0];
                    }
                }
                else if (cmd == "vertex") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        vec3 vert = vec3(values[0], values[1], values[2]);
                        triVerts.push_back(vert);
                    }
                }
                else if (cmd == "vertexnormals") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        //not used eh.
                    }
                }

                else if (cmd == "tri") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {

                        vec3 v1 = triVerts[values[0]];
                        vec3 v2 = triVerts[values[1]];
                        vec3 v3 = triVerts[values[2]];
                        Triangle* obj = new Triangle(v1, v2, v3);


                        // Set the object's light properties

                        obj->ambient = ambient;
                        obj->emission = emission;
                        obj->diffuse = diffuse;
                        obj->specular = specular;
                        obj->shininess = shininess;
                        obj->type = "triangle";

                        // Set the object's transform
                        obj->transform = t_stack.top();
                        obj->InversedTransform = glm::inverse(t_stack.top());
     
                        this->objList.push_back(obj);

                        //Object* obj1 = objList.back();
                        /*cout << obj1->type << "\n";
                        cout << obj1->transform[0][0] << obj1->transform[1][0] << obj1->transform[2][0] << obj1->transform[3][0] << "\n";
                        cout << obj1->transform[0][1] << obj1->transform[1][1] << obj1->transform[2][1] << obj1->transform[3][1] << "\n";
                        cout << obj1->transform[0][2] << obj1->transform[1][2] << obj1->transform[2][2] << obj1->transform[3][2] << "\n";
                        cout << obj1->transform[0][3] << obj1->transform[1][3] << obj1->transform[2][3] << obj1->transform[3][3] << "\n";
                        cout << "\n";*/
                        
                    }
                }

                else if (cmd == "trinormal") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {

                        //figure out for shading

                    }
                }
                

                else if (cmd == "translate") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE.  
                        // Think about how the transformation stack is affected
                        // You might want to use helper functions on top of file. 
                        // Also keep in mind what order your matrix is!
                        mat4 tMat = Transform::translate(values[0], values[1], values[2]);
                        rightmultiply(tMat, t_stack);
                    }
                }
                else if (cmd == "scale") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE.  
                        // Think about how the transformation stack is affected
                        // You might want to use helper functions on top of file.  
                        // Also keep in mind what order your matrix is!

                        mat4 sMat = Transform::scale(values[0], values[1], values[2]);
                        rightmultiply(sMat, t_stack);
                    }
                }
                else if (cmd == "rotate") {
                    validinput = readvals(s, 4, values);
                    if (validinput) {

                        // YOUR CODE FOR HW 2 HERE. 
                        // values[0..2] are the axis, values[3] is the angle.  
                        // You may want to normalize the axis (or in Transform::rotate)
                        // See how the stack is affected, as above.  
                        // Note that rotate returns a mat3. 
                        // Also keep in mind what order your matrix is!

                        mat3 r = Transform::rotate(values[3], vec3(values[0], values[1], values[2]));
                        mat4 rMat = mat4(r[0][0], r[0][1], r[0][2], 0,
                            r[1][0], r[1][1], r[1][2], 0,
                            r[2][0], r[2][1], r[2][2], 0,
                            0, 0, 0, 1);

                        rightmultiply(rMat, t_stack);

                    }
                }

                // I include the basic push/pop code for matrix stacks
                else if (cmd == "pushTransform") {
                    t_stack.push(t_stack.top());
                }
                else if (cmd == "popTransform") {
                    if (t_stack.size() <= 1) {
                        cerr << "Stack has no elements.  Cannot Pop\n";
                    }
                    else {
                        t_stack.pop();
                    }
                }

                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline(in, str);
        }

        // Set up initial position for eye, up and amount
        // As well as booleans 

        
        /*
        eye = eyeinit;
        up = upinit;
        amount = 5;
        sx = sy = 1.0;  // keyboard controlled scales in x and y 
        tx = ty = 0.0;  // keyboard controllled translation in x and y  
        useGlu = false; // don't use the glu perspective/lookat fns
        */
        

        glEnable(GL_DEPTH_TEST);
    }
    else {
        cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
}



Readfile::Readfile() {
    outputFile = "output.png";
    t_stack.push(mat4(1.0));
    objList = vector<Object*>();
    lightList = vector<Lighting*>();
    triVerts = vector<vec3>();
    triNorms = vector<vec3>();
    maxDepth = 5;
    ambient = vec3(0.2, 0.2, 0.2);
    diffuse = vec3(0, 0, 0);
    emission = vec3(0, 0, 0);
    specular = vec3(0, 0, 0);
    shininess = 0.0f;
    attenuation[0] = 1.0f;
    attenuation[1] = 0.0f;
    attenuation[2] = 0.0f;
}


Readfile::~Readfile()
{
}



