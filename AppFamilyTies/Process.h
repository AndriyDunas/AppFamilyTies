#ifndef PROCESS_H
#define PROCESS_H

#include "general.h"

class Process {
public:
  Process() : _procInfo("start") {};
  ~Process() {};

  void SaveInfo(DWORD pid);
  void GetInfo(HWND fhwnd);
  void DisplayInfo(HWND hwnd) const;
  bool StartsAtStartup() const;
  void ToggleStartup() const;

private:
  std::string _procInfo;
};

#endif  // !PROCESS_H