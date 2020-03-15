#include "Timer.h"

const int DEFAULT_UPDATE_PERIOD = 5000; // ms

Timer::Timer() {
  _updatePeriod = DEFAULT_UPDATE_PERIOD;
  _timer = 0;
}

void Timer::Set(HWND hwnd) {
  _timer = SetTimer(hwnd, TIMER_ID, _updatePeriod, NULL);
}

void Timer::Kill(HWND hwnd) {
  KillTimer(hwnd, TIMER_ID);
  _timer = 0;
}