#ifndef PROCESS_H
#define PROCESS_H
#include "linux_parser.h"
#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                               
  std::string User();                      
  std::string Command();                 
  float CpuUtilization() const;        
  std::string Ram();                      
  long int UpTime();                      
  bool operator<(Process const& a) const;

 private:
 int _pid;
 std::string _user;
 std::string _command;
 double _cpuutilization;
 std::string _ram;
 long int _uptime;

};

#endif