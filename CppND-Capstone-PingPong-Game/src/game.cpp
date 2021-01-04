#include "game.h"
#include <iostream>
#include "SDL.h"
#include <stdlib.h>

Game::Game(std::size_t grid_width, std::size_t grid_height, std::size_t screen_width, std::size_t screen_height)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
	  bat(screen_width, screen_height, grid_width, grid_height),
      ball((float)screen_width/2,(float)screen_height/2,(float)(rand()%359)){
        ball.screen_width = screen_width; ball.screen_height = screen_height, ball.grid_width = grid_width, ball.grid_height = grid_height;
}
 

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, bat);
    Update();
    renderer.Render(bat, ball);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  if (ball.GameOver) return;
  bat.Update();
  ball.Update(bat);

  //checking if ball hit the bat and increasing the speed if so
  if (ball.ballHitBat == true)
  {
    score++;
    ball.speed+=0.1;
  }
}

int Game::GetScore() const { return score; }