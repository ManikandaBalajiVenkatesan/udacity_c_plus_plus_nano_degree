#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

using std::vector;

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  Process(int pid_):pid(pid_){}	;
  void proc_stat(int pid_);
  
  // TODO: Declare any necessary private members
 private:
  int pid;
  long utime, stime, cutime, cstime, starttime;
  float cpu_usage;
};

#endif