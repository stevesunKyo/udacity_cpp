#include <string>

#include "format.h"

using std::string;
using std::to_string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  long hour, min, sec;
  hour = seconds / 3600;
  min = (seconds - hour * 3600) / 60;
  sec = (seconds - hour * 3600 - min * 60);
  return to_string(hour) + ":" + to_string(min) + ":" + to_string(sec);}