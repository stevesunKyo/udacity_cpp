#include "processor.h"

// Return the CPU utilization
float Processor::Utilization() {
  // _utils: vector<string>
  // _totaltime: long
  long idle_prev, idle_now, total_prev, total_now;
  idle_prev = LinuxParser::IdleJiffies();
  total_prev = LinuxParser::Jiffies();
  sleep(0.5);
  // read cpu information twice to calculate cpu usage data
  idle_now = LinuxParser::IdleJiffies();
  total_now = LinuxParser::Jiffies();

  double totaldiff, idlediff;
  totaldiff = (double)total_now -(double) total_prev;
  idlediff = (double)idle_now - (double)idle_prev;
  
  return (totaldiff - idlediff) / totaldiff;}