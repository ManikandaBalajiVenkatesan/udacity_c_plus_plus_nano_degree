#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

using std::string;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor Parsing();
  float cpu_utilization;
  string cpu_name;
  int user, nice, system;
  int idle, iowait, irq;
  int softirq, steal;
  int total_idle, total_non_idle;
  int total;
  
  // TODO: Declare any necessary private members
 private:

  

  
};

#endif