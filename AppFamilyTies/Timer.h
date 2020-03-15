#ifndef TIMER_H
#define TIMER_H

#include "general.h"

class Timer {
public:
  Timer();
  ~Timer() {};

  void Set(HWND hwnd);
  void Kill(HWND hwnd);
  void SetUpdatePeriod(int seconds) { _updatePeriod = seconds * 1000; }
  // wtf з типом повернення має бути int
  UINT_PTR GetUpdatePeriod(void) const { return _updatePeriod; }
  UINT_PTR GetUpdateTimer(void) const { return _timer; }

private:
  UINT_PTR _timer;
  int _updatePeriod;
};

#endif  // !TIMER_H