#ifndef RANDOM_H
#define RANDOM_H

float rand01(){
  float random = float(rand());
  return float(random / RAND_MAX);
}

Math::vec3 RandomInSphere(){
  //Rejection method to generate a random point in sphere

  Math::vec3 p;
  do{
    p = 2.0f * Math::vec3(rand01(), rand01(), rand01()) - Math::vec3(1.0f);
  }while(Math::dot(p, p) >= 1.0f);
  return p;
}

#endif
