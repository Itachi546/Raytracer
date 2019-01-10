#ifndef RAY_H
#define RAY_H

namespace Math{

  struct Ray{
    vec3 origin;
    vec3 direction;

    Ray(){}
    Ray(const vec3&  o, vec3 d){
      origin = o;
      direction = d;
    }

    inline vec3 GetOrigin() const {
      return origin;
    }
    inline vec3 GetDirection() const {
      return direction;
    }

    inline vec3 PointAt(float t){
      return origin + t * direction;
    }
    
    
  };

}
#endif
