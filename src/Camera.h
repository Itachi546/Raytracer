#ifndef CAMERA_H
#define CAMERA_H

#include "Math/Math.h"

struct Camera{
  Math::vec3 llc;
  Math::vec3 horizontal;
  Math::vec3 vertical;
  Math::vec3 origin;

  Camera(){
    llc = {-2.0f, -1.0f, -1.0f};
    origin = {0, 0, 0};
    horizontal = {4.0f, 0.0f, 0.0f};
    vertical = {0.0f, 3.0f, 0.0f};
  }

  Math::Ray GetRay(float u, float v){
    return Math::Ray(origin, llc + u * horizontal + v * vertical - origin);
  }
};

#endif
