#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "bat.h"
#include "ball.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::size_t screen_width, std::size_t screen_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;

 private:
  Bat bat;
  Ball ball;
  
  int theta_l = 0, theta_h = 359;	//min and max angle of attack of ball
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_theta;

  int score{0};

  void Update();

};

#endif