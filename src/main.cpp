#include <iostream>
#include <stdint.h>
#include <random>
#include <fstream>
#include "Camera.h"
#include "Material.h"
#include "Window.h"

const int WIDTH = 200;
const int HEIGHT = 100;

Math::vec3 Color(Math::Ray& ray, HitableList* world, int depth){
  HitRecord hit;
  //target is calculated by vector algebra
  //hitPoit + normal gives vector from origin to center and random is sphere is the vector
  //from the center of sphere to its surface
  //adding the vector gives any arbitary point on unit sphere
  //spherical direction of reflection of light
  //absorb half of the light and reflect half of the light
  if(world->Hit(ray, 0.0f, FLT_MAX, hit)){
    Math::Ray scattered;
    Math::vec3 attenuation;
    if(depth < 50.0f && hit.mat_ptr->scatter(ray, hit, attenuation, scattered))
      return attenuation * Color(scattered, world, depth + 1);
    else
      return Math::vec3(0, 0, 0);
  }
  Math::vec3 unit_direction = Math::normalize(ray.direction);
  float t = 0.5f * (unit_direction.y + 1.0f);
  return (1.0f - t) * Math::vec3(1.0f) + t * Math::vec3(0.5f, 0.7f, 1.0f);
}

int main(int argc, char ** argv)
{
  std::ofstream image("image.ppm");
  Window window;
  window.Init(WIDTH, HEIGHT);
  if(!image){
    std::cout << "failed to open image" << std::endl;
    return 0;
  }
  
  image << "P3\n" << WIDTH <<" " << HEIGHT << "\n255\n";
  Camera camera;
  Hitable* list[4];
  list[0] = new Sphere(Math::vec3(0, 0, -1), 0.5f, new Lambertian(Math::vec3(0.8f, 0.3f, 0.3f)));
  list[1] = new Sphere(Math::vec3(0, -100.5, -1), 100.0f, new Lambertian(Math::vec3(0.8f, 0.8f, 0.0f)));
  list[2] = new Sphere(Math::vec3(1, 0, -1), 0.5f, new Metallic(Math::vec3(0.8f, 0.6f, 0.2f), 0.5f));
  list[3] = new Sphere(Math::vec3(-1, 0, -1), 0.5f, new Metallic(Math::vec3(0.8f, 0.8f, 0.8f), 0.9f));
  HitableList* world = new HitableList(list, 4);
  int ns = 100; //number of samples
  for(int j = HEIGHT; j >=0; --j){
    for(int i = 0; i < WIDTH; ++i){
      Math::vec3 col;
      if(!window.Run())
	return 0;

      for(int s = 0; s < ns; ++s){
	Math::vec2 uv = {float(i + rand01()) / float(WIDTH), float(j + rand01()) / float(HEIGHT)};	
	Math::Ray ray =  camera.GetRay(uv.x, uv.y);
	col += Color(ray, world, 0);
      }
      col = col / float(ns);
      col = {sqrt(col.x), sqrt(col.y), sqrt(col.z)};
      int r = int(col.r * 255.99);
      int g = int(col.g * 255.99);
      int b = int(col.b * 255.99);
      image << r <<" " << g <<" " << b << "\n";
      window.PlotPixel(i, HEIGHT - j, r, g, b);
    }
  }

  while(window.Run()){
    
  }
  window.Destroy();


  return 0;
}
