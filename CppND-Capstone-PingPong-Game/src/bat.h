#ifndef BAT_H
#define BAT_H

#include "SDL.h"
#include <stdio.h>

class Bat
{
	public:
    
    	enum Direction { kLeft, kRight, kRest };
    	Bat(int _screen_width, int _screen_height, int _grid_width, int _grid_height)
        	:screen_width(_screen_width),
        	 screen_height(_screen_height),
             grid_width(_grid_width),
        	 grid_height(_grid_height),
             x(screen_width / 2),
             y(screen_height-grid_height/2),
             h(grid_height),		//height of bat one grid_height 
             w(4*grid_width) { }	//width of bat 4 grid_width
        //parameter of the bat
        int screen_width, screen_height;
        int grid_width, grid_height;
    	int x, y;	//x & y coordinate of center of rectangular bat
        int h ;	//height of the bat 
        int w ;	//width of the bat
        bool isRest = true;	//indicating that the bat is in rest position
        Direction direction = Direction::kRest;	//initializing the bat to be at rest
        int batLeftLimit() const {return x - w/2;}
        int batRightLimit() const {return x + w/2;}
        int batTopLimit() const {return y - h/2;}
        void setBatPos(int speed);
        void Update();
        int speed = 10;	//speed of bat
        
    private:
  



};

#endif