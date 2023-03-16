#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System(){
kernel_ = LinuxParser::Kernel();
uptime_ = LinuxParser::UpTime();
totalprocesses_ = LinuxParser::TotalProcesses();
os_ = LinuxParser::OperatingSystem();
runningprocesses_ = LinuxParser::RunningProcesses();
memutil_ = LinuxParser::MemoryUtilization();
vector<int> pids = LinuxParser::Pids();
for (auto items:pids){processes_.push_back(Process(items));}
// add all processes with some pids into vector processes_
std::sort(processes_.begin(), processes_.end());}
  
// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel_; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return memutil_; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return os_; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return runningprocesses_; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return totalprocesses_; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return uptime_; }
