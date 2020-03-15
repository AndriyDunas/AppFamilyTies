#ifndef TRAYICON_H
#define TRAYICON_H

#include "general.h"

class TrayIcon {
public:
 explicit TrayIcon(HWND hwnd);
 ~TrayIcon();

 void AddToTray(void);

private:
  NOTIFYICONDATA _notifyIconData;
};

#endif  // !TRAYICON_H