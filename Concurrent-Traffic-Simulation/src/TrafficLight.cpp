#include <iostream>
#include <random>
#include "TrafficLight.h"


/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
  std::unique_lock<std::mutex> ulock(_mutex);
  _cond.wait(ulock, [this] {return !_queue.empty();});
  T msg = std::move(_queue.back());
  _queue.pop_back();
  return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
  std::lock_guard<std::mutex> ulock(_mutex);
  _queue.push_back(std::move(msg));
  _cond.notify_one();
}

/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

TrafficLight::~TrafficLight(){} // Acturally, do nothing

void TrafficLight::waitforGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
  while(true){
  TrafficLightPhase new_item = _msgqueue.receive();
  if (new_item == TrafficLightPhase::green){break;}
  std::this_thread::sleep_for(_ms(100));
  // sleep for 0.1s between each loop
  }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::setCurrentPhase(TrafficLightPhase light)
{
    _currentPhase = light;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class.
  std::thread t(&TrafficLight::cycleThroughPhases, this);
  _threads.emplace_back(std::move(t));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{ 
    static std::default_random_engine engine;
    static std::uniform_int_distribution<unsigned> wait_time(4000, 6000);

    while (true){
        std::this_thread::sleep_for(_ms{wait_time(engine)});
        if (_currentPhase == TrafficLightPhase::green){_currentPhase = TrafficLightPhase::red;}
        else{_currentPhase = TrafficLightPhase::green;}
        _msgqueue.send(std::move(_currentPhase));
        std::this_thread::sleep_for(_ms{1});
    }
}
