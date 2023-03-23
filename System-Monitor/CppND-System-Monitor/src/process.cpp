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
  long uptime = LinuxParser::UpTime();
  long total_time, start_time, utime, stime, cutime, cstime;
  double cpuu= 0.0;
  string value, line;
  std::ifstream filestream("/proc/" + to_string(_pid) + "/stat");
  if (filestream.is_open()){
  std::getline(filestream, line);
  std::istringstream linestream(line);
  int count = 0;
  while (linestream >> value){
  count ++;
  if (count == 14){utime = stol(value);}
  else if (count == 15) {stime = stol(value);}
  else if (count == 16) {cutime = stol(value);}
  else if (count == 17) {cstime = stol(value);}
  else if (count == 22) {start_time = stol(value);}
  }
  total_time = stime + utime + cutime + cstime;
  double total_time_hz = ((double)total_time/sysconf(_SC_CLK_TCK));
  double seconds = ((double)uptime-((double)start_time/sysconf(_SC_CLK_TCK)));
  cpuu = total_time_hz/seconds;
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