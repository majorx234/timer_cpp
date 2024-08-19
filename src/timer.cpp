#include "timer.hpp"

//template
Timer::Timer(std::function<void()> func, unsigned time_in_millisec, RunMode run_mode)
  : ok(true)
  , timeInMillisec(time_in_millisec)
  , newCMsg(false)
  , runMode(run_mode)
  , started(false)

{
  //std::function<void(void)> thrd_fnct = [&func](){};
  functToCall = func;
  if((runMode == RunMode::once)||(runMode == RunMode::forever))
  {
    timerThrd = std::thread(&Timer::timerFct,this);
    started = true;
  }

}

Timer::~Timer(){
  ok = false;
  timerThrd.join();
}

void Timer::timerFct(){
  while(ok)
  {
    std::unique_lock<std::mutex> lck(cMutex);
    if(!newCMsg){
      while (cCv.wait_for(lck,std::chrono::milliseconds(timeInMillisec))==std::cv_status::timeout) {
        if(!ok){
          return;
        }
        functToCall();
        if(runMode == RunMode::once){
          return;
        }
      }
    }
    // if reset do something
    newCMsg = false;
  }
  started = false;
}

void Timer::reset()
{
  if (ok){
      std::unique_lock<std::mutex> lck(cMutex);
      newCMsg = true;
      cCv.notify_all();
    }
}

void Timer::stop(){
  ok = true;
  timerThrd.join();
  started = false;
}

void Timer::restart(){
  if (started)
  {
    stop();
  }
  start();
}

void Timer::start(){
  if((runMode == RunMode::once_stopped)||(runMode == RunMode::forever_stopped))
  {
    if (!started)
    {
      timerThrd = std::thread(&Timer::timerFct,this);
      started = true;
    }
  }
}
