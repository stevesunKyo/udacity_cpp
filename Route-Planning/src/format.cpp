#include <string>

#include "format.h"

using std::string;
using std::to_string;

// if numbers is 0 to 9, format it to 00, 01 ... 09.
string add_zero(long numbers){
  string result;
  if(numbers < 10){
   result = "0" + to_string(numbers);
   return result;}
  return to_string(numbers);
}


// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  long hour, min, sec;
  string hours, mins, secs;
  hour = seconds / 3600;
  min = (seconds - hour * 3600) / 60;
  sec = (seconds - hour * 3600 - min * 60);  
  return add_zero(hour) + ":" + add_zero(min) + ":" + add_zero(sec);}