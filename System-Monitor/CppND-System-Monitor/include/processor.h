#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include "linux_parser.h"
#include <unistd.h>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();
  std::vector<float> Utilization_each();
  std::vector<string> Cpu_Name();
 private:

};

#endif