# CPPND: Program a Concurrent Traffic Simulation

In this project , concept of threads running in parallel , exchange of data between threads , access protection of memory locations have been implemented to simulate a traffic intersection.
The system consists of moving vehicles and traffic signals at intersection.
Each run in their own thread in a concurrent fashion. The vehicles move along the road and cross the intersection , on reaching every intersection their next goal is randomly choosen.
The vehicles wait at the intersection for their chance to go through which is controlled by the signal thread which queues the incoming vehicle and provide permission to move forward.
The signal toggles between red and green enums at a random interval between 4 to 6 seconds.
On green the signal provides permission to the first vehicle in queue to pass through. 
Mutex has been used to lock memory access shared by threads, condition variables & notifications to indicate arrival of new data in queue variable.

![](data/sim_out.gif)

## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./traffic_simulation`.

![](data/sim_cmd_out.gif)
