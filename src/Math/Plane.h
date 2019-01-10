#ifndef PLANE_H
#define PLANE_H

#include "Algebra/vec.h"
#include "Algebra/operation.h"

namespace Math{

  class Plane{

  public:
    vec3 normal;
    float distance;

    Plane(){}

    Plane(const vec3& normal, const float& distance){
      this->normal = normal;
      this->distance = distance;
    }

    Plane(const vec3& p0, const vec3& p1, const vec3& p2){
      Set(p0, p1, p2);
    }
    
    void Set(const vec3& normal, const float& distance){
      this->normal = normal;
      this->distance = distance;
    }

    void Set(const vec3& p0, const vec3& p1, const vec3& p2){
      vec3 e1 = p1 - p0;
      vec3 e2 = p2 - p0;
      normal = normalize(cross(e1, e2));
      distance = -dot(normal, p0);
    }

    float Distance(const vec3& p){
      //distance between plane and point
      //distance between normal and point + distance of plane from origin
      return (dot(p, normal)) + distance;
    }
  
    vec3 Project(const vec3& p){
      float dis = Distance(p);
      return  (p - dis * normal);
    }
  
  };

}
#endif
