#ifndef MATERIAL_H
#define MATERIAL_H

#include "Math/Math.h"
#include "Primitives.h"
#include "Random.h"

struct Material{

  virtual bool scatter(const Math::Ray& ray_in, const HitRecord& info, Math::vec3& attenuation, Math::Ray& ray_scattered) = 0;
  
};

struct Lambertian : public Material{

  Math::vec3 albedo;
  Lambertian(Math::vec3 color){
    albedo = color;
  }
  Lambertian(){}
  virtual bool scatter(const Math::Ray& ray_in, const HitRecord& info, Math::vec3& attenuation, Math::Ray& ray_scattered){
    Math::vec3 reflect = info.point + info.normal + RandomInSphere();
    ray_scattered.direction = reflect - info.point;
    ray_scattered.origin = info.point;
    attenuation = albedo;
    return true;
  }
};

struct Metallic : public Material{

  Math::vec3 albedo;
  float fuzziness; //control the bluring of reflection
  Metallic(Math::vec3 color, float fuzziness){
    albedo = color;
    this->fuzziness = fuzziness;
  }
  Metallic(){}
  virtual bool scatter(const Math::Ray& ray_in, const HitRecord& info, Math::vec3& attenuation, Math::Ray& ray_scattered){
    Math::vec3 reflect = Math::reflect(Math::vec3(ray_in.direction), info.normal);
    ray_scattered.direction = reflect - info.point + fuzziness * RandomInSphere();
    ray_scattered.origin = info.point;
    attenuation = albedo;
    return Math::dot(reflect, info.normal) > 0.0f;
  }
};

#endif
