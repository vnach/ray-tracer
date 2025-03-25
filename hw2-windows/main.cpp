/******************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi  */
/* Extends HW 1 to deal with shading, more transforms and multiple objects    */
/******************************************************************************/

// You shouldn't have to edit this file at all!

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glew.h>
#include <GL/glut.h>
//#include "shaders.h"
#include "Transform.h"
#include <FreeImage.h>
//#include "UCSD/grader.h"
//#include "Geometry.h"

#include <iostream>

using namespace std; 

// Main variables in the program.  
#define MAINPROGRAM 
//#include "variables.h" 
#include "Camera.h"
#include "Object.h"
#include "Readfile.h" // prototypes for readfile.cpp  
#include "Raytracer.h"


void saveScreenshot(string fname, Readfile* rf) {

  FreeImage_Initialise();
  //int pix = w * h;
  //BYTE *pixels = new BYTE[3*pix];	
  //glReadBuffer(GL_FRONT);
  //glReadPixels(0,0,w,h,GL_BGR,GL_UNSIGNED_BYTE, pixels);

  int w = rf->width;
  int h = rf->height;

  Camera camera = rf->cam;
  cout << "lookFrom: " << camera.lookFrom[0] << camera.lookFrom[1] << camera.lookFrom[2];
  cout << " look At: " << camera.lookAt[0] << camera.lookAt[1] << camera.lookAt[2];
  cout << " up: " << camera.up[0] << camera.up[1] << camera.up[2];
  cout << " fovy: " << camera.fovy;
  cout << "\n";

  
  
  FIBITMAP* img = FreeImage_Allocate(w, h, 24);
  RGBQUAD color;
  vec3 lookFrom = vec3(0, 0, 0);
  vec3 lookAt = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  float fovy = 90;

  
  //Camera* cam = new Camera(lookFrom, lookAt, up, fovy);
  /*Sphere* s = new Sphere(vec3(0, 0, 0), 1);
  s->ambient = vec3(0, 1, 0);
  stack <mat4> tstack;
  tstack.push(mat4(1.0));
  mat4 tMat = Transform::translate(0, 0, .5);
  tstack.top() = tstack.top() * tMat;
  mat3 r = Transform::rotate(45, vec3(0, 0, 1));
  mat4 rMat = mat4(r[0][0], r[0][1], r[0][2], 0,
      r[1][0], r[1][1], r[1][2], 0,
      r[2][0], r[2][1], r[2][2], 0,
      0, 0, 0, 1);

  tstack.top() = tstack.top() * rMat;
  mat4 sMat = Transform::scale(1.0, 0.25, 0.25);
  tstack.top() = tstack.top() * sMat;

  s->transform = tstack.top();
  s->InversedTransform = glm::inverse(tstack.top());

  Sphere* s1 = new Sphere(vec3(0, 0, 0), 1);
  s1->ambient = vec3(1, 0, 0);
  stack <mat4> tstack2;
  tstack2.push(mat4(1.0));
  mat4 tMat1 = Transform::translate(0, 0, .5);
  tstack2.top() = tstack2.top() * tMat1;
  r = Transform::rotate(-45, vec3(0, 0, 1));
  mat4 rMat1 = mat4(r[0][0], r[0][1], r[0][2], 0,
      r[1][0], r[1][1], r[1][2], 0,
      r[2][0], r[2][1], r[2][2], 0,
      0, 0, 0, 1);

  tstack2.top() = tstack2.top() * rMat1;
  mat4 sMat1 = Transform::scale(1.0, 0.25, 0.25);
  tstack2.top() = tstack2.top() * sMat1;

  s1->transform = tstack2.top();
  s1->InversedTransform = glm::inverse(tstack2.top());


  rf->objList = vector<Object*>();

  rf->objList.push_back(s);
  rf->objList.push_back(s1);*/
  


  vec3 v1 = vec3(-1, -1, 0);
  vec3 v2 = vec3(1, -1, 0);
  vec3 v3 = vec3(1, 1, 0);
  vec3 v4 = vec3(-1, 1, 0);
  
  Triangle* t1 = new Triangle(v1, v2, v3);
  
  #pragma omp parallel for
  for (int i = 0; i < w; i++) {
      for (int j = 0; j < h; j++) {

          Ray ray = camera.createRay(i, j);
          
          Raytracer tr = Raytracer();
          
          //Intersection hit = tr.findIntersection(ray, rf);

          vec3 c = tr.findColor(ray, rf, 0);
          //!(s->hitObj(ray)).isHit
          /*if (s->hitObj(ray).isHit) {
              color.rgbRed = 255;
              color.rgbGreen = 0;
              color.rgbBlue = 0;
          }*/

          color.rgbRed = c[0] * 255;
          color.rgbGreen = c[1] * 255;
          color.rgbBlue = c[2] * 255;

          if (i % 100 == 0 && j % 100 == 00) {
              cout << i << " " << j << "\n";
          }

          /*color.rgbRed = i;
          color.rgbGreen = j;
          color.rgbBlue = i + j;*/
    

          FreeImage_SetPixelColor(img, i, h-j, &color);
      }
  }

  FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);

  //FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

  std::cout << "Saving screenshot: " << fname << "\n";

  FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
}


int main(int argc, char* argv[]) {

  if (argc < 2) {
    cerr << "Usage: transforms scenefile [grader input (optional)]\n"; 
    exit(-1); 
  }

  Readfile* file = new Readfile();
  

  file->readfile(argv[1]);
  saveScreenshot(file->outputFile, file);

  FreeImage_DeInitialise();
  return 0;
}
