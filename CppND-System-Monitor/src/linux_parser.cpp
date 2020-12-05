#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"


using std::stof;
using std::stoi;
using std::stol;
using std::string;
using std::to_string;
using std::vector;
using std::cout;

// BONUS: Update this to use std::filesystem

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, ver;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> ver >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  float mem_free, mem_total, mem_available, buffers;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()){
    while (std::getline(stream, line)){
      std::istringstream linestream(line);
      string param;
      linestream >> param;
      if ( param == "MemTotal:") {  linestream >> mem_total;}
      if ( param == "MemFree:") {  linestream >> mem_free;}
      if ( param == "MemAvailable:") { linestream >> mem_available;}
      if ( param == "Buffers:") { linestream >> buffers; }
 
      
    }
    //if (mem_total && mem_free){ int mem_usage = mem_total - mem_free; return mem_usage;} 
  	if (mem_total && mem_free && buffers){ float mem_usage = 1.0 - (mem_free / (mem_total - buffers)) ; return mem_usage;}
    
  }
  
  
   }
// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
    return stol(uptime);
  }
  //return 0; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; } 


// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  int num_processes;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()){
    while (std::getline(stream, line)){
      std::istringstream linestream(line);
      string param;
      linestream >> param;
      if ( param == "processes") {  linestream >> num_processes; return num_processes;}
    }
    
  }
  return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  int running_processes;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()){
    while (std::getline(stream, line)){
      std::istringstream linestream(line);
      string param;
      linestream >> param;
      if ( param == "procs_running") {  linestream >> running_processes; return running_processes;}
    }
    
  }return 0; }


// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string pid_s = to_string(pid);
  string line;
  std::ifstream stream( LinuxParser::kProcDirectory + pid_s + LinuxParser::kCmdlineFilename);
  if (stream.is_open()){
    std::getline(stream,line);
    
    
  }
  return line;
  
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function


string LinuxParser::Ram(int pid) {
  string line; 
  int process_memory;
  string pid_s = to_string(pid);
  
  std::ifstream stream( LinuxParser::kProcDirectory + pid_s + LinuxParser::kStatusFilename);
  if (stream.is_open()){
    while (std::getline(stream, line)){
      std::istringstream linestream(line);
      string param;
      linestream>>param;
      if (param == "VmSize:"){
        linestream>>process_memory;
      }
    }
  }
  process_memory = process_memory / 1024;
  string process_memory_string = to_string(process_memory);
  //cout<<pid<<"\t"<<process_memory<<"\n";
  return process_memory_string; }


// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  
  string pid_s = to_string(pid);
  string line;
  int uid;
  std::ifstream stream( LinuxParser::kProcDirectory + pid_s + LinuxParser::kStatusFilename);
  if (stream.is_open()){
   	while (std::getline(stream, line)){
      	
    	std::istringstream linestream(line);
      	string param;
      	linestream >> param;
		if (param == "Uid:"){
         
         linestream >> uid;
         //cout<<pid<<"\t"<<uid<<"\n";
         return to_string(uid); 
        }
    }
  }
  
   }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function


string LinuxParser::User(int pid) { 
  int uid = stoi(LinuxParser::Uid(pid));
  string line, line_data, user_name, user_passwd, user_uid;
  std::ifstream stream( LinuxParser::kPasswordPath);
  if (stream.is_open()){
  	while (std::getline(stream, line)){
      	std::istringstream linestream(line);
      	linestream>> line_data;
      	std::istringstream userstream(line_data);
      	std::getline(userstream,user_name,':');
      	std::getline(userstream,user_passwd,':');
      	std::getline(userstream,user_uid,':');
      	if (stoi(user_uid) == uid){
          return user_name;
        }
        }
    }
   }



// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { return 0; }