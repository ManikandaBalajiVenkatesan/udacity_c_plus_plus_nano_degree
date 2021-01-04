#ifndef BALL_H
#define BALL_H

#include "SDL.h"
#include "bat.h"
#include "renderer.h"

class Ball
{
	public:
    	Ball(float _x, float _y, float _theta):x(_x), y(_y), theta(_theta){}
        void Update(Bat const bat);	//to update position of ball
       
        float x;	//ball x coordinate
        float y;	//ball y coordinate
        float theta;	//ball angle of attack 
     	float speed = 3.0f;	//speed of ball
		std::size_t screen_width{0};
  		std::size_t screen_height{0};
  		std::size_t grid_width{0};
  		std::size_t grid_height{0};
        float ballLeftLimit();
        float ballRightLimit();
        float ballBottomLimit();
        float ballTopLimit();
        bool ballHitBat = false;	//flag that indicates whether bat had hit the ball
        bool GameOver = false;		//flag indicating game is over, when ball goes below bat then game over
        
    private:
    	float ball_left_x{0.0};
        float ball_right_x{0.0};
        float ball_bottom_y{0.0};
        float ball_top_y{0.0};
};

#endif