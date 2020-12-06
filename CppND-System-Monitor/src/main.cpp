#include "ncurses_display.h"
#include "system.h"
#include<string>
#include<iostream>
#include<chrono>
#include <thread>
#include <iomanip>

#include "format.h"

using std::cout;
using std::string;
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int main() {
  System system;
  
  NCursesDisplay::Display(system);
}