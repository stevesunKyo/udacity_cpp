#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
// constructor of class pid. initialize the variables.

// calculate cpu utilization of a process
  long uptime = LinuxParser::UpTime(_pid);
  long total_time, start_time;
  double cpuu= 0.0;
  string value, line;
  std::ifstream filestream("/proc/[" + to_string(_pid) + "]/stat");
  if (filestream.is_open()){
  std::getline(filestream, line);
  std::istringstream linestream(line);
  for (int i = 0; i < 30; i++){
  linestream >> value;
    switch(i){
      case 13:
        total_time = total_time + stol(value);
      case 14:
        total_time = total_time + stol(value);
      case 15:
        total_time = total_time + stol(value);
      case 16:
        total_time = total_time + stol(value);
      case 21:
        start_time = stol(value);
    	break;}
  }
  cpuu = 100*(double)total_time/((double)uptime*sysconf(_SC_CLK_TCK)-(double)start_time);
  } 
  
_pid = pid;
_user = LinuxParser::User(pid);
_command = LinuxParser::Command(pid);
_cpuutilization = cpuu;
_ram = LinuxParser::Ram(pid);
_uptime = LinuxParser::UpTime(pid);}

// Return this process's ID
int Process::Pid() { return _pid; }

// Return this process's CPU utilization. this stores in /proc/[pid]/stat folder. 
float Process::CpuUtilization() const {return _cpuutilization; }

// Return the command that generated this process
string Process::Command() { return _command; }

// Return this process's memory utilization
string Process::Ram() { return _ram; }

// Return the user (name) that generated this process
string Process::User() { return _user; }

// Return the age of this process (in seconds)
long int Process::UpTime() { return _uptime; }

// Overload the "less than" comparison operator for Process objects, which will be used in sorting processes with cpuutilization.
bool Process::operator<(Process const& a) const {return a.CpuUtilization() < this->CpuUtilization();}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     