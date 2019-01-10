#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "Math/Math.h"

struct Material;

struct HitRecord{
  float t; //distance from the position
  Math::vec3 point;// point
  Math::vec3 normal; //normal vector 
  Material* mat_ptr;
};

class Hitable{
 public:
  virtual bool Hit(Math::Ray& ray, float t_min, float t_max, HitRecord& hit) = 0;
};


class Sphere : public Hitable{
 public:
  Math::vec3 center;
  float radius;
  Material* material;
  Sphere(){}
 Sphere(Math::vec3 center, float radius, Material* mat) : center(center), radius(radius){
    material = mat;
  }
  virtual bool Hit(Math::Ray& ray, float t_min, float t_max, HitRecord& hit){
    //Sphere ray intersection
    //Equation (x - x1)2 + (y - y1)2 + (z - z1)2 = r2;
    //p = (x, y, z) and c=(x1, y1, z1)
    //dot(p-c, p-c) = r2 p = o + r * d //origin and ray direction
    //simplifying and comparing with at2 + bt + c = 0
    //find the discriminant if b2 - 4ac >= 0 then we have intersection
    //@Note ray direction is not a unit vector
  
    Math::vec3 oc = ray.origin - center;
    float a = Math::lengthSquared(ray.direction);
    float b = 2 * Math::dot(oc, ray.direction);
    float c = Math::lengthSquared(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if(discriminant > 0){
      float temp = (- b - sqrt(discriminant)) / (2.0f * a);
      if(temp > t_min && temp < t_max){
	hit.t = temp;
	hit.point = ray.PointAt(temp);
	hit.normal = Math::normalize(hit.point - center);
	hit.mat_ptr = material;
	return true;
      }
      temp = (-b + sqrt(discriminant)) / (2.0f * a);
      if(temp > t_min && temp < t_max){
	hit.t = temp;
	hit.point = ray.PointAt(temp);
	hit.normal = Math::normalize(hit.point - center);
	hit.mat_ptr = material;
	return true;
      }
    }
    return false;
  }
};


class HitableList : public Hitable{
 public:
  Hitable** list;
  int list_size;
  
  HitableList(){}
  HitableList(Hitable** hl, int n){
    list = hl;
    list_size = n;
  }
  
  virtual bool Hit(Math::Ray& ray, float t_min, float t_max, HitRecord& hit){
    HitRecord temp;
    bool hitAnything = false;
    double closest = t_max;
    for(int i = 0; i < list_size; ++i){
      if(list[i]->Hit(ray, t_min, t_max,  temp)){
	hitAnything = true;
	if(closest > temp.t){
	  closest = temp.t;
	  hit = temp;
	}
      }
    }
    return hitAnything;
  }


};

#endif
