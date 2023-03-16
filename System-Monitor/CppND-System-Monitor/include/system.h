#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  System();
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      

 private:
  Processor cpu_={};
  std::vector<Process> processes_ = {};
  float memutil_ = 0.0;
  long uptime_ = 0;
  int totalprocesses_ = 0;
  int runningprocesses_ = 0;
  std::string kernel_ = " ";
  std::string os_ = " ";
  
};

#endif