#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"
#include "stdlib.h"
#include <vector>

using _ms = std::chrono::milliseconds;
// more easy to define milliseconds


// forward declarations to avoid include cycle
class Vehicle;

enum TrafficLightPhase {red,green};

template <class T>
class MessageQueue
{
public:
   T receive();
   void send(T &&msg);
private:
   std::mutex _mutex;
   std::condition_variable _cond;
   std::deque<T> _queue;
};

class TrafficLight
{
public:
    // constructor / desctructor
    TrafficLight();
    ~TrafficLight();
    // getters / setters
    TrafficLightPhase getCurrentPhase();
    void setCurrentPhase(TrafficLightPhase light);
    // typical behaviour methods
    void waitforGreen();
    void simulate();
private:
    // typical behaviour methods
    void cycleThroughPhases();
    TrafficLightPhase _currentPhase;
    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.
    MessageQueue<TrafficLightPhase> _msgqueue;
    std::vector<TrafficLightPhase> queue; 
    std::condition_variable _condition;
    std::mutex _mutex;
    std::vector<std::thread> _threads;
};

#endif