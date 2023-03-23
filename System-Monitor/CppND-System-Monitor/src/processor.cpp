#include "processor.h"
#include <iostream>
using std::cout;
using std::endl;

// Return the CPU utilization for each cpu and total cpu
std::vector<float> Processor::Utilization_each(){
  std::vector<std::vector<long>> jiffies_prev = LinuxParser::CpuUtil_each();
  sleep(1);
  std::vector<std::vector<long>> jiffies_now = LinuxParser::CpuUtil_each();
  std::vector<std::vector<long>> different;
  std::vector<float> result;
  int numbers_of_cpu = jiffies_prev.size();
  for (int i = 0; i < numbers_of_cpu; i++){
  std::vector<long> temp;
  for (int j = 0; j < 2; j++){
   temp.push_back(jiffies_now[i][j] - jiffies_prev[i][j]);// calculate the difference of idle and total jiffies.
  }
   different.push_back(temp);
  }
  for (int i = 0; i< numbers_of_cpu; i++){
  result.push_back( ((float)different[i][1] - (float)different[i][0])/(float)different[i][1] );
  // (totaldiff - idlediff ) / totaldiff; 
  }
  return result;
}

// Return the CPU utilization
float Processor::Utilization() {
  // _utils: vector<string>
  // _totaltime: long
  long idle_prev, idle_now, total_prev, total_now;
  idle_prev = LinuxParser::IdleJiffies();
  total_prev = LinuxParser::Jiffies();
  //cout << total_prev << endl;
  sleep(1);
  // read cpu information twice to calculate cpu usage data
  idle_now = LinuxParser::IdleJiffies();
  total_now = LinuxParser::Jiffies();
  //cout << total_now << endl;
  float totaldiff, idlediff;
  totaldiff = (float)total_now -(float) total_prev;
  idlediff = (float)idle_now - (float)idle_prev;
  if (totaldiff == 0){
  cout << "Failed to read Jiffies data." << endl;
  return 0.0;}
  else{return (totaldiff - idlediff) / totaldiff;}}

// Return the Cpu names;
std::vector<string> Processor::Cpu_Name(){
  std::vector<string> result = LinuxParser::CpuName();
  return result;
}