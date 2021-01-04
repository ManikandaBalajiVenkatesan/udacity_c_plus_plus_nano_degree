#include "controller.h"
#include <iostream>
#include "SDL.h"



void Controller::HandleInput(bool &running, Bat &bat) const 
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) 
  {
    if (e.type == SDL_QUIT) 
    {
      running = false;
    } 
    else if (e.type == SDL_KEYDOWN) 
    {
      switch (e.key.keysym.sym) 
      {
        case SDLK_LEFT:
          bat.direction = Bat::Direction::kLeft;
          bat.isRest = false;
          break;

        case SDLK_RIGHT:
          bat.direction = Bat::Direction::kRight;
          bat.isRest = false;
          break;
      }
    }
  }
}