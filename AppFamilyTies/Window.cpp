#include "Window.h"

extern const TCHAR *APP_NAME;
const TCHAR defaultClassName[] = "Default Class Name";

Window::Window(HINSTANCE hInstance) {
  memset(&_wnd, 0, sizeof(WNDCLASSEX));
  _wnd.hInstance = hInstance;
  _wnd.lpszClassName = defaultClassName;
  _wnd.lpfnWndProc = WndProc;
  _wnd.style = CS_HREDRAW | CS_VREDRAW;
  _wnd.cbSize = sizeof(WNDCLASSEX);
  _wnd.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  _wnd.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  _wnd.hCursor = LoadCursor (NULL, IDC_ARROW);
  _wnd.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
  _fhwnd = NULL;

  if (RegisterClassEx(&_wnd)) {
    _hwnd = CreateWindowEx(0, _wnd.lpszClassName, APP_NAME, 
      WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, defaultWidth, defaultHeight, 0, NULL, hInstance, NULL);
  } else {
    _hwnd = NULL;
  }
}

void Window::Show(void) const {
  ShowWindow(_hwnd, SW_HIDE);
}