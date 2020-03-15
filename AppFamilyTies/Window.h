#ifndef WINDOW_H
#define WINDOW_H

#include "general.h"

class Window {
public:
  explicit Window(HINSTANCE hInstance);
  ~Window(){}

  void Show(void) const;
  HWND GetOurWindow(void) const { return _hwnd; }
  void SetForeground(void) { _fhwnd = GetForegroundWindow(); }
  HWND GetForeground(void) const { return _fhwnd; }

private:
  // copy operations are private to prevent copying
  Window(const Window&);
  Window& operator=(const Window&);

  HWND _hwnd;  // handle of our window
  HWND _fhwnd;   // handle of foreground window
  WNDCLASSEX _wnd;
};

#endif // !WINDOW_H