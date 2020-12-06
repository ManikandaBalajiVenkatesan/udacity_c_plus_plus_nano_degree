#include <string>
#include <iostream>

#include "format.h"

using std::string;
using std::to_string;
using std::cout;

//Complete this helper function


string Format::string_conv(int data)
{
  string data_s = to_string(data);
  if (data < 10)
  	data_s = "0"+data_s;
  return data_s;
}

string Format::ElapsedTime(long seconds) { 
  int hours = seconds / 3600;
  int sec = seconds - (hours * 3600);
  int minutes = sec / 60;
  
  int seconds_left = sec%60;
  
  string hours_s = Format::string_conv(hours);
  string sec_s = Format::string_conv(seconds_left);
  string minutes_s = string_conv(minutes);
  string time = hours_s + ":" + minutes_s + ":" + sec_s; 
  return time; }