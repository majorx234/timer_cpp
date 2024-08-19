#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

//template
class Timer {
public:
  enum RunMode {once ,forever ,once_stopped ,forever_stopped};
  Timer(std::function<void()> func, unsigned time_in_millisec, RunMode run_mode);
  ~Timer();
  void timerFct();
  void reset();
  void stop();
  void restart();
  void start();
private:
  std::function<void()> functToCall;
  std::thread timerThrd;
  std::atomic_bool ok;
  unsigned int timeInMillisec;
  std::mutex cMutex;
  std::atomic_bool newCMsg;
  std::condition_variable cCv;
  RunMode runMode;
  std::atomic_bool started;
};

#endif // TIMER_HPP_
