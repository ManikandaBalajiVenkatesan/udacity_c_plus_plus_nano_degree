#include "bat.h"
#include <stdio.h>
#include <iostream>

void Bat::Update()
{
  	if (isRest == true)
      direction = Direction::kRest;
  
 	switch(direction)
    {
      case Direction::kLeft:
        if (batLeftLimit()<=0)		//to restrict bat going out of left side of screen
          setBatPos(0);
        else
          setBatPos(-speed);
        isRest = true;
        break;
      case Direction::kRight:
        if (batRightLimit()>=screen_width)	//to restrict bat going out of right side of screen
          setBatPos(0);
        else
          setBatPos(speed);
        isRest = true;
        break;
      case Direction::kRest:
        setBatPos(0);
        break;   
    }
}

void Bat::setBatPos(int speed)
{
  x+= speed;
}

