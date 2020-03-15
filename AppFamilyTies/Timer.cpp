#include "Timer.h"

Timer::Timer() {
  _updatePeriod = 5000;  // magic
  _timer = 0;
}

void Timer::Set(HWND hwnd) {
  _timer = SetTimer(hwnd, TIMER_ID, _updatePeriod, NULL);
}

void Timer::Kill(HWND hwnd) {
  KillTimer(hwnd, TIMER_ID);
  _timer = 0;
}