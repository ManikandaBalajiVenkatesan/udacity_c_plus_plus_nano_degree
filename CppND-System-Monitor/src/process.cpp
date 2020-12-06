#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::cout;

//Return this process's ID
int Process::Pid() { 
  return this->pid; }

//Return this process's CPU utilization
float Process::CpuUtilization() { 
  float clock_freq = sysconf(_SC_CLK_TCK);
  float cpu_uptime = LinuxParser::UpTime();
  Process::proc_stat(this->pid);
  
  long total_time = this->utime + this->stime + this->cutime + this->cstime;
  long seconds = cpu_uptime - ( this->starttime / clock_freq);
  this->cpu_usage= ((total_time / clock_freq) / seconds);
  
  return this->cpu_usage; }


//function to parse stat file contents
void Process::proc_stat(int pid){
  string line, data;
  string pid_s = to_string(pid);
  std::ifstream stream(LinuxParser::kProcDirectory + pid_s +  LinuxParser::kStatFilename);
   if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int count = 1;
    while ( count <= 22){
      linestream >> data ;
      if (count == 14){this->utime = stol(data);}
      else if (count == 15){this->stime = stol(data);}
      else if (count == 16){this->cutime = stol(data);}
      else if (count == 17){this->cstime = stol(data);}
      else if (count == 22){this->starttime = stol(data);}
      count = count + 1;
    }
  }
}


//Return the command that generated this process
string Process::Command() {  return LinuxParser::Command(this->pid); }

//Return this process's memory utilization
string Process::Ram() {  return LinuxParser::Ram(this->pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->pid); }

//Return the age of this process (in seconds)
long int Process::UpTime() { 
  float cpu_uptime = LinuxParser::UpTime();
  float clock_freq = sysconf(_SC_CLK_TCK);
  Process::proc_stat(this->pid);
  float process_uptime = cpu_uptime - (this->starttime/clock_freq);
  
  return process_uptime; }

//Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
  return  (this->cpu_usage >  a.cpu_usage); }
  