#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;

// Read data from the filesystem
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

// Read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}


// Read Pids and store them into a vector<int>
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
  // return all of the pids, stored in a vector<int>. 
  return pids;
}

// Read and return the memory utilization
float LinuxParser::MemoryUtilization() {
  float MemTotal = 1.0;
  float MemFree = 1.0;  // initialize to avoid 0 division
  string line, keyname, value;
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if (filestream.is_open()){
    while (std::getline(filestream, line)){ // read mem files in each line
    // information were stored in format 
    // Name:   Value + kB
    std::istringstream linestream(line);
    linestream >> keyname >> value;
    if (keyname == "MemTotal:"){MemTotal = stof(value);}
    if (keyname == "MemFree:"){MemFree = stof(value);}}
    return (MemTotal - MemFree)/MemTotal;}
  else{return 0.0;}}

// Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime, line;
  std::ifstream filestream(kProcDirectory+kUptimeFilename);
  if (filestream.is_open()){
  std::getline(filestream, line);
  std::istringstream linestream(line);
  linestream >> uptime;
  return stol(uptime);  
  }
  return 0; }

// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  // this should return the number of ticks system made since the last boot.
  // jiffies = activejiffies + idlejiffies
  return ActiveJiffies()+IdleJiffies();}

// Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  // Active Jiffies is the sum of the following times.
  // utime, stime, cutime, cstime
  // these items were stored in the 13~16 th number (0 index) in the /proc/[pid]/stat file
  vector <string> jiffies;
  string line, value;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
  if (filestream.is_open()){
  std::getline(filestream, line);
  std::istringstream linestream(line);
  while (linestream >> value){jiffies.push_back(value);}
  return stol(jiffies[13])+stol(jiffies[14])+stol(jiffies[15])+stol(jiffies[16]);
  // numbers were stored in No.13~No.16 places in vector.
  }
  return 0; }

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  // Active Jiffies for a system is the sum of the following times.
  // user, nice, system, irq, softirq, steal;
  vector<string> jiffies = CpuUtilization();
  if (jiffies.size() > 0){ // sanity check, incase CpuUtilization did not read anything
  long result = stol(jiffies[CPUStates::kUser_]) + stol(jiffies[CPUStates::kNice_]) + stol(jiffies[CPUStates::kSystem_]) + stol(jiffies[CPUStates::kIRQ_]) + stol(jiffies[CPUStates::kSoftIRQ_]) + 	 stol(jiffies[CPUStates::kSteal_]);
    return result;}    
  else{return 0;}
}

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  // idle jiffies is the sum of the following times.
  // Idle, IOwait;
  vector<string> jiffies = CpuUtilization();
  if (jiffies.size() > 0){ // sanity check, incase CpuUtilization did not read anything
  long result = stol(jiffies[kIdle_]) + stol(jiffies[kIOwait_]);
    return result;}
  else{return 0;}
}

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, cpu, value;
  vector<string> jiffies;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
  std::getline(filestream, line);
  std::istringstream linestream(line);
  linestream >> cpu;
  while (linestream >> value){jiffies.push_back(value);}
  // write the total "jiffies" read from /proc/stat from "cpu" row into vectors.
  return jiffies;}
  cout << "CpuUtilization Failed to Read Data" << endl;
  return {}; }

// Read and return CPU utilization, for EACH CPU and total CPU.
vector<vector<long>> LinuxParser::CpuUtil_each(){
// use similiar way to read CPU util.
// it will return a vector containing idle jiffies and total jiffies.
  string line, cpuname, value;
  vector<vector<long>> jiffies;
  vector<vector<long>> result;
  int rowindex = 0;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
  while(std::getline(filestream, line)){
  // get one line until the end;
  std::istringstream linestream(line);
  linestream >> cpuname;
    if (cpuname == "intr"){break;}// ""
    else{while(linestream >> value){jiffies[rowindex].push_back(stol(value));}} // end of else
  rowindex ++;} // end of while:getline
  } // end of open filestream
  int jiffies_size = jiffies.size();
  for (int i=0; i<jiffies_size; i++){
  vector<long> tmp;
  tmp.push_back(jiffies[i][3]+jiffies[i][4]); //  idle jiffies =[3] + [4]
  tmp.push_back(jiffies[i][0]+jiffies[i][1]+jiffies[i][2]+jiffies[i][3]+jiffies[i][4]+jiffies[i][5]+jiffies[i][6]+jiffies[i][7]); // total jiffies = [0] + [1] + ... [7]
  result.push_back(tmp);
  } 
  return result;}

// Read and return all CPU names;
vector<string> LinuxParser::CpuName(){
  string line, cpuname;
  vector<string> result;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
  while(std::getline(filestream, line)){;
  std::istringstream linestream(line);
  linestream >> cpuname;
  if (cpuname == "intr"){break;}                                     
  else{result.push_back(cpuname);}}
  return result;}
  return {}; 
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string name,value, line;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()){
  while (std::getline(filestream, line)){
   std::istringstream linestream(line);
   linestream >> name >> value;
   if (name == "processes"){return stoi(value);}}}
  return 0; }

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string name, value, line;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()){
  while (std::getline(filestream, line)){
  std::istringstream linestream(line);
  linestream >> name >> value;
  if (name == "procs_running"){return stoi(value);}
  }}
  return 0; }

// Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string name, value, line, not_used;
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
  if (filestream.is_open()){
  std::getline(filestream, line);
  std::istringstream linestream(line);
  linestream >> value;
  return value;}
  return string(); }

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string name, value, line;
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
  while (std::getline(filestream, line)){
  std::istringstream linestream(line);
  linestream >> name >> value;
  if (name == "VmSize:"){
    string result = to_string(stof(value)/1024);
    string::size_type position = result.find(".");
    result.erase(position+3, result.length());
    return result; }}} // round it to 2 digit decimals
  return string(); }

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  // pid is one of the ids stored in vector pid<int> returned by function Pid 
  string name, value, line;
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if (filestream.is_open()){
  while (std::getline(filestream, line)){
  std::istringstream linestream(line);
  linestream >> name >> value;
  if (name == "Uid:"){return value;}
  } }
  return string(); }

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string uid, value, line, not_used;
  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open()){
  while (std::getline(filestream, line)){
  std::replace(line.begin(), line.end(), ':', ' ');
  std::istringstream linestream(line);
  linestream >> value >> not_used >> uid;
  // value is the user name, name is the "pid"
  if(uid == Uid(pid)){break;}}}
  return value; }

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  string name, value, line;
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatFilename);
  value = "";
  if(filestream.is_open()){
  std::getline(filestream, line);
  std::istringstream linestream(line);
  for(int i=0; i<10000; i++){
  linestream >> value; // take "value" out;
  if (i == 21){// 21: starttime
    break;}
  }
  return stol(value) / sysconf(_SC_CLK_TCK);
  }
  return 0; }
