#ifndef WINDOW_H
#define WINDOW_H
#include <SDL/SDL.h>
class Window{
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  bool running = true;
 public:
  Window(){
    window = nullptr;
    renderer = nullptr;
  }
  void Init(int width, int height){
      SDL_Init(SDL_INIT_VIDEO);
      window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
      renderer = SDL_CreateRenderer(window, -1, 0);
  }
  void PlotPixel(int x, int y, int r, int g, int b){
    SDL_SetRenderDrawColor(renderer, r, g, b, 0);
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderPresent(renderer);
  }
  bool Run(){
    while(SDL_PollEvent(&event)){
      switch (event.type)
	{
	case SDL_QUIT:
	  running = false;
	  break;
	}
    }

    return running;
  }

  void Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
};

#endif
