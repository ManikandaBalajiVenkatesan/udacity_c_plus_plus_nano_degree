#include "ball.h"


#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

void Ball::Update(Bat const bat)
{
  ballHitBat = false;	//resetting flag
  float random = (rand() - rand())%20;	//adding random angle to deflection angle instead of just angle of incidence = angle of reflection
  float theta_rad = theta*M_PI/180.0;
  float dx = speed*cos(theta_rad);
  float dy = speed*sin(theta_rad);
  //printf("dx %lf dy %lf\n",dx,dy);
  x = x + dx;
  y = y - dy;
  
  if (ballLeftLimit() <= 0.0 || ballRightLimit() >= 640.0)	//ball hitting left wall or right wall
    if(theta <= 180.0)
      theta = 180 - theta;
  	else if(theta >180.0)
      theta = 360.0 - (theta-180.0);
  
  if (ballTopLimit() <= 0.0)	//ball hitting top wall
    theta = 360.0 - theta;
  
  if (ballBottomLimit() >= bat.batTopLimit())	//checking ball below bat surface
  {
    if (ballRightLimit() >= bat.batLeftLimit() && ballLeftLimit() <= bat.batRightLimit())	//checking if ball is hitting the bat
    {
      ballHitBat = true;	//setting flag
      theta = std::max(std::min(360.0 - theta + random,180.0),0.0);
      
    }
  	else
    {
      GameOver = true;
     printf("game over\n"); 
    }
  }
  //printf("bat pos in ball x %d, y %d\n",bat.x*(int)(screen_width/grid_width), bat.y*(int)(screen_height/grid_height));
  //printf("bat left %d, right %d\n",bat_left, bat_right);
  //printf("ball x %lf, ball y %lf theta %lf theta_rad %lf\n",x,y,theta,theta_rad);
}


float Ball::ballLeftLimit()
{
  ball_left_x = x - 0.5*(float)(screen_width/grid_width);
  return ball_left_x;
}

float Ball::ballRightLimit()
{
  ball_right_x = x + 0.5*(float)(screen_width/grid_width);
  return ball_right_x;
}

float Ball::ballBottomLimit()
{
  ball_bottom_y = y + 0.5*(float)(screen_width/grid_width);
  return ball_bottom_y;
}

float Ball::ballTopLimit()
{
  ball_top_y = y - 0.5*(float)(screen_width/grid_width);
  return ball_top_y;
}