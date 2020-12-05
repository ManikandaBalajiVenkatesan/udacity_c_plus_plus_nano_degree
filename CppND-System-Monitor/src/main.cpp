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
  
  /*cout<<"os name is "<<system.OperatingSystem()<<"\n";
  cout<<"kernel is "<<system.Kernel()<<"\n";
  cout<<"memory utilization "<<system.MemoryUtilization()<<"\n";
  cout<<"number of processes "<<system.TotalProcesses()<<"\n";
  cout<<"number of running processes "<<system.RunningProcesses()<<"\n";
  cout<<"Up time is "<<system.UpTime()<<"\n";
  */
  
  system.Cpu();
  // system.Processes();
  //char uptime = Format::ElapsedTime(system.UpTime()).c_str(); 
  //cout<<uptime;
  
  /*
  int i=0;
  while (i == 0)
  {
    float cpu = system.Cpu().Utilization();
    cout<<cpu<<"\n";
    string uptime = Format::ElapsedTime(system.UpTime());
    cout<<uptime<<"\n";
    sleep_for(1s);
  }
*/
  
  //float mem = system.MemoryUtilization();
  //cout<<mem;
  //system.Processes();
  
 
  /*
  long seconds = 1;
  while (seconds < 7200){
    cout<<"Up time is "<<system.UpTime()<<"\t"<<Format::ElapsedTime(system.UpTime()).c_str()<<"\n";
    //cout<<Format::ElapsedTime(seconds).c_str()<<"\n";
    seconds = seconds + 1;
    sleep_for(1000ms);
  }
*/
  NCursesDisplay::Display(system);
}