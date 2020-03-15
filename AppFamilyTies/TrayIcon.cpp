#include "TrayIcon.h"

extern const TCHAR *APP_NAME;

TrayIcon::TrayIcon(HWND hwnd) {
  memset(&_notifyIconData, 0, sizeof(NOTIFYICONDATA));
  _notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
  _notifyIconData.hWnd = hwnd;
  _notifyIconData.uID = APP_TRAY_ICON;
  _notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
  _notifyIconData.uCallbackMessage = WM_TRAYICON; 
  strcpy_s(_notifyIconData.szTip, APP_NAME);
}

TrayIcon::~TrayIcon() {
  Shell_NotifyIcon(NIM_DELETE, &_notifyIconData);
}

void TrayIcon::AddToTray(void) {
  Shell_NotifyIcon(NIM_ADD, &_notifyIconData);
}